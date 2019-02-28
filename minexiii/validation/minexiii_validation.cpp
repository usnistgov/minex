/*
 * This software was developed at the National Institute of Standards and
 * Technology (NIST) by employees of the Federal Government in the course
 * of their official duties. Pursuant to title 17 Section 105 of the
 * United States Code, this software is not subject to copyright protection
 * and is in the public domain. NIST assumes no responsibility whatsoever for
 * its use by other parties, and makes no guarantees, expressed or implied,
 * about its quality, reliability, or any other characteristic.
 */

#include <sys/stat.h>
#include <arpa/inet.h>

#include <libgen.h>

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <system_error>
#include <vector>

#include <minexiii.h>
#include <minexiii_validation.h>
#include <minexiii_validation_data.h>

void
MINEXIII::printUsage(
    char *name)
{
	std::cerr << "Usage: " << name << " {create|match|pid} "
	    "[random seed]" << std::endl;
}

int
main(
    int argc,
    char *argv[])
{
	int rv = EXIT_FAILURE;

	if ((argc < 2) || (argc > 3)) {
		MINEXIII::printUsage(argv[0]);
		return (rv);
	}
	
	/* Parse random seed, if present */
	std::mt19937_64::result_type randomSeed{std::random_device()()};
	if (argc == 3) {
		try {
			randomSeed = std::stoll(argv[2]);
		} catch (std::exception) {
			std::cerr << "Random seed: an error occurred when "
			    "converting \"" << argv[2] << "\" to an integer." <<
			    std::endl;
			MINEXIII::printUsage(argv[0]);
			return (rv);
		}
	}

	std::string operation{argv[1]};
	if (operation == "create") {
		try {
			MINEXIII::testCreation(MINEXIII::IMAGES_DIR,
			    randomSeed);
			rv = EXIT_SUCCESS;
		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
	} else if (operation == "match") {
		try {
			MINEXIII::testMatching(randomSeed);
			rv = EXIT_SUCCESS;
		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
	} else if (operation == "pid") {
		MINEXIII::testLibraryID();
		rv = EXIT_SUCCESS;
	} else
		MINEXIII::printUsage(argv[0]);

	return (rv);
}

std::string
MINEXIII::createTemplate(
    const std::string &rawPath)
{
	/* Obtain image metadata */
	MINEXIII::ImageMetadata metadata;
	std::unique_ptr<char[]> bname(new char[rawPath.length() + 1]);
	std::strncpy(bname.get(), rawPath.c_str(), rawPath.length() + 1);
	std::string filename(basename(bname.get()));
	
	try {
		metadata = MINEXIII::SAMPLE_DATA.at(filename.c_str());
	} catch (std::out_of_range) {
		throw std::runtime_error("Could not find metadata for " +
		    rawPath);
	}

	/* Create template */
	auto rawData = MINEXIII::readFile(rawPath);
	uint8_t outputTemplate[MINEX_MAX_TEMPLATE_SIZE * 3]{0};
	int32_t rv = create_template(rawData.get(), metadata.quality,
	    metadata.position, metadata.impression, metadata.height,
	    metadata.width, outputTemplate);

	/* Read template size from template */
	uint16_t templateSize;
	std::memcpy(&templateSize, outputTemplate + 8, 2);
	templateSize = ntohs(templateSize);

	/* Output results */
	std::string outputPath{MINEXIII::OUTPUT_DIR + "/" + filename + ".tmpl"};
	std::ofstream file{outputPath,
	    std::ofstream::binary | std::ofstream::out};
	if (!file)
		throw std::runtime_error("Could not open " + outputPath);
	file.write((char *)outputTemplate, templateSize);
	if (!file)
		throw std::runtime_error("Could not write " + outputPath);
	file.close();

	return (filename + '\t' + std::to_string(rv) + '\t' +
	    std::to_string(templateSize));
}

void
MINEXIII::testCreation(
    const std::string &imageDirPath,
    std::mt19937_64::result_type randomSeed)
{
	/* Create output directory */
	if (mkdir(MINEXIII::OUTPUT_DIR.c_str(), S_IRWXU | S_IRWXG) != 0) {
		std::system_error error{errno, std::system_category()};
		if (error.code().value() != EEXIST)
			throw std::runtime_error{"Could not create directory " +
			    MINEXIII::OUTPUT_DIR + " (" + error.what() + ")"};
	}

	/* Shuffle image list before matching */
	auto rng = std::mt19937_64(randomSeed);
	std::vector<std::string> images;
	images.reserve(MINEXIII::SAMPLE_DATA.size());
	for (const auto &imageData : MINEXIII::SAMPLE_DATA)
		images.push_back(imageData.first);
	std::shuffle(images.begin(), images.end(), rng);

	std::cout << "Input\tRV\tTemplateSize\n";
	for (const auto &imageName : images)
		std::cout << MINEXIII::createTemplate(imageDirPath + "/" +
		    imageName) << std::endl;
}

std::unique_ptr<uint8_t[]>
MINEXIII::readFile(
    const std::string &pathName)
{
	std::ifstream file{pathName,
	    std::ifstream::ate | std::ifstream::binary};
	if (!file)
		throw std::runtime_error{"Could not open " + pathName};
	file.unsetf(std::ifstream::skipws);

	uint64_t size = file.tellg() -
	    std::ifstream::pos_type(std::ifstream::beg);
	if (size == -1)
		throw std::runtime_error{"Could not open " + pathName};
	auto buf = std::unique_ptr<uint8_t[]>(new uint8_t[size]);
	file.seekg(std::ifstream::beg);
	file.read((char *)buf.get(), size);
	if (!file)
		throw std::runtime_error{"Could not read " + pathName};
	file.close();

	return (buf);
}

std::string
MINEXIII::matchTemplates(
    const std::string &verificationName,
    const std::string &enrollmentName)
{
	auto verificationTmpl = MINEXIII::readFile(MINEXIII::OUTPUT_DIR + '/' + 
	    verificationName);
	auto enrollmentTmpl = MINEXIII::readFile(MINEXIII::OUTPUT_DIR + '/' + 
	    enrollmentName);

	float similarity;
	int32_t rv = match_templates(verificationTmpl.get(),
	    enrollmentTmpl.get(), &similarity);
	
	return (verificationName + '\t' + enrollmentName + '\t' +
	    std::to_string(rv) + '\t' + std::to_string(similarity));
}

void
MINEXIII::testMatching(
    std::mt19937_64::result_type randomSeed)
{
	std::cout << "VerificationName\tEnrollmentName\tRV\tSimilarity\n";

	/* Shuffle pairs list before matching */
	auto rng = std::mt19937_64(randomSeed);
	auto pairs = std::vector<std::pair<std::string, std::string>>(
	    MINEXIII::SAMPLE_PAIRS.begin(), MINEXIII::SAMPLE_PAIRS.end());
	std::shuffle(pairs.begin(), pairs.end(), rng);

	for (const auto &pair : pairs) 
		std::cout << MINEXIII::matchTemplates(pair.first,
		    pair.second) << std::endl;
}

void
MINEXIII::testLibraryID()
{
	std::cout << "GProduct\tGVersion\tMProduct\tMVersion\n";
	uint32_t generator, matcher;
	uint32_t productMask = 0xFFFF0000, versionMask = 0x0000FFFF;
	get_pids(&generator, &matcher);
	std::cout << std::setw(4) << std::setfill('0') << std::hex <<
	    ((generator & productMask) >> 16) << '\t';
	std::cout << std::setw(4) << std::setfill('0') << std::hex <<
	    (generator & versionMask) << '\t';
	std::cout << std::setw(4) << std::setfill('0') << std::hex <<
	    ((matcher & productMask) >> 16) << '\t';
	std::cout << std::setw(4) << std::setfill('0') << std::hex <<
	    (matcher & versionMask) << std::endl;
}

