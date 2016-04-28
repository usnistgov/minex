/*
 * This software was developed at the National Institute of Standards and
 * Technology (NIST) by employees of the Federal Government in the course
 * of their official duties. Pursuant to title 17 Section 105 of the
 * United States Code, this software is not subject to copyright protection
 * and is in the public domain. NIST assumes no responsibility whatsoever for
 * its use by other parties, and makes no guarantees, expressed or implied,
 * about its quality, reliability, or any other characteristic.
 */

#ifndef MINEXIII_VALIDATION_H_
#define MINEXIII_VALIDATION_H_

#include <memory>
#include <string>

namespace MINEXIII
{
	/** Directory containing validation imagery */
	const std::string IMAGES_DIR{"validation_imagery_raw"};
	/** Directory where created templates should be written */
	const std::string OUTPUT_DIR{"validation_output"};

	/**
	 * @brief
	 * Perform template creation validation.
	 *
	 * @param imageDirPath
	 * Path to directory of PGM images.
	 * @param randomSeed
	 * Value to use when seeding the random number generator.
	 *
	 * @throw std::logic_error
	 * Invalid template created.
	 * @throw std::runtime_error
	 * Error reading imagery or creating output directory.
	 */
	void
	testCreation(
	    const std::string &imageDirPath,
	    std::mt19937_64::result_type randomSeed);

	/**
	 * @brief
	 * Create a template.
	 * 
	 * @param rawPath
	 * Path to a raw image file.
	 *
	 * @return
	 * "rawPath RV templateSize"
	 *
	 * @throw std::logic_error
	 * Invalid template created.
	 * @throw std::runtime_error
	 * Error reading imagery.
	 */
	std::string
	createTemplate(
	    const std::string &rawPath);

	/**
	 * @brief
	 * Match two templates
	 *
	 * @param verificationName
	 * Name of the file to load as the verification template.
	 * @param enrollmentName
	 * Name of the file to load as the enrollment template.
	 *
	 * @return
	 * "verificationName enrollmentName RV similarity"
	 *
	 * @throw std::runtime_rror
	 * Error reading template.
	 */
	std::string
	matchTemplates(
	    const std::string &verificationName,
	    const std::string &enrollmentName);
	
	/**
	 * @brief
	 * Perform template matching validation.
	 *
	 * @param randomSeed
	 * Value to use when seeding the random number generator.
	 *
	 * @throw std::runtime_error
	 * Error reading pairslist.
	 */
	void
	testMatching(
	    std::mt19937_64::result_type randomSeed);

	/**
	 * @brief
	 * Test the get_pid() MINEX API function.
	 */
	void
	testLibraryID();
	
	/**
	 * @brief
	 * Read a file
	 * 
	 * @param pathName
	 * Path to file to read.
	 *
	 * @return
	 * Contents of pathname
	 *
	 * @throw runtime_error
	 * Error opening or reading pathname.
	 */
	std::unique_ptr<uint8_t[]>
	readFile(
	    const std::string &pathName);
	
	/**
	 * @brief
	 * Print application usage to stderr.
	 *
	 * @param name
	 * Name of the executable.
	 */
	void
	printUsage(
	    char *name);
}

#endif /* MINEXIII_VALIDATION_H_ */

