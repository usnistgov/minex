MINEX III Validation
====================

The Minutia Interoperability Exchange (MINEX) III validation package is used to
help ensure that software submitted for MINEX III runs as expected on NIST's
hardware and to help participants eliminate errors in their software before
submitting to NIST. This helps reduce the overall runtime of the evaluation and
provide a higher level of confidence that the results presented by NIST are a
true measure of the submitted software.

*For more general information about participation in MINEX III, please
visit the [MINEX III participation webpage].*

Package Contents
----------------

 * Interaction Required:
     * [`config/`]:
       Directory where all required configuration files must be placed. You
       might not have any configuration files.
     * [`lib/`]:
       Directory where all required libraries must be placed. There must
       be at least one "core" library, and that library **must** follow the
       MINEX III naming convention.
     * [`validate`]:
       Script to automate running the validation driver and perform sanity
       checks on the output.
 * Supporting Files:
     * [`Makefile`]:
     Builds the validation source code files.
     * [`minexiii.h`]:
     API specification for MINEX III.
     * [`minexiii_validation.cpp`]:
     C++ source code for the validation driver.
     * [`minexiii_validation.h`]:
     C++ header  for the validation driver.
     * [`minexiii_validation_data.h`]:
       Header containing metadata for the imagery in `validation_imagery_raw`.
     * `validation_imagery_raw/`:
       Directory where decompressed validation fingerprint imagery resides.
     * [`VERSION`]:
       Version number of the validation package.


Requirements
------------

The MINEX III validation package is required to be run on CentOS 7.6.1810. This
is not the latest version of CentOS 7, but it is being required to remain
consistent. The OS version may be updated periodically. An ISO of CentOS
7.6.1511 is freely available as a direct download from the [CentOS vault]
([🇺🇸 USA], [🇪🇺 Europe]) or the [NIST mirror]. The following packages are
required to be installed:

`centos-release`, `coreutils`, `curl`, `gawk`, `gcc-c++`, `grep`, `iputils`,
`make`, `sed`, `which`, `yum`

It is highly suggested that you ensure your submission will build and run as
expected on environments as close as possible to the NIST evaluation machines,
in order to avoid validation delays.

How to Run
----------

 1. Place your MINEX III software libraries in the `lib` directory.
 2. Place any configuration files in the `config` directory.
 3. (*Optional*) Export the software/marketing name of the algorithms under test
    in the following environment variables. For example:
	* `export MINEXIII_GENERATOR_MARKETING_NAME="mindtct 2.3"`
	* `export MINEXIII_MATCHER_MARKETING_NAME="bozorth3 5.0.1"`
 4. Export the environment variable `MINEXIII_GENERATOR_ONLY` to `TRUE` if your
    submission does not contain a template matcher:
    - `export MINEXIII_GENERATOR_ONLY=TRUE`
 4. Execute `./validate`
 5. **If successful**, sign *and* encrypt the resulting output archive in a
    single step, and upload it, along with the encrypting identity's public key,
    and your original signed evaluation agreement via [the MINEX upload form].
    If unsuccessful, correct any errors described and try again.

Submission Contents
-------------------

Upon successful completion of the MINEX III validation package, an archive is
generated that must be signed and encrypted before submitting to NIST.
Participants are strongly encouraged to look at the output of this archive to
ensure that information generated is as expected. Validation log files and
fingerprint templates should not be modified, because their contents must be
generated identically on NIST's systems.

Some runtime information is logged, which is also included in the output.
Absolute file paths are present in these files. Participants should feel free to
replace absolute file paths they deem sensitive with relative file paths, so
long as the meaningful validation information remains present. Files that may
contain paths that can be edited are **bolded** below.

 * `cbeff.log`: The output of running `time minexiii_validation pid` and the
   contents of the following environment variables:
	* `MINEXIII_GENERATOR_MARKETING_NAME`
	* `MINEXIII_MATCHER_MARKETING_NAME`
 * **`compile.log`**: The output of running `time make`, the MD5 checksum of the
   contents of `lib` and `config`, the output of `ldd` on `minexiii_validation`,
   and the current version of the operating system.
 * `config/`: A copy of `config`.
 * `create.log`: The output of running `time minexiii_validation create`.
 * `lib/`: A copy of `lib`.
 * `match.log`: The output of running `time minexiii_validation match`.
 * `templates/`: Fingerprint templates generated when creating `create.log`.

Checks Performed
----------------

The following high-level checks are performed by this package:

 * Necessary validation packages have been installed by `yum`.
 * Validation package is at most recent revision level.
 * Appropriate operating system version is used.
 * Appropriately named MINEX III software library is present.
 * Configuration files are read-only, if applicable.
 * No previous validation attempts exist in the output directory.
 * Software library links properly against the validation driver.
 * CBEFF information in library is reflected correctly in software library name.
 * A large number of templates can be created in succession.
 * All templates are generated without errors.
 * A large number of templates can be matched in succession.
 * All matching operations return successfully.

While the validation package tries to eliminate errors from the MINEX III
submission, there are still several ways in which the package might approve
you for submittal but NIST would later reject you:

 * Software links against dynamic libraries in the dynamic linker path that are
   not present on NIST systems.
 * The most current version of the validation package was not used.
 * Library with this CBEFF version number has already been submitted to NIST.
 * Templates created at NIST do not match templates submitted.
 * Similarity scores created at NIST do not match similarity scores submitted.
 * Submitted software is non-deterministic.
 * Submitted validation package is not signed and encrypted.
 * Submitted validation package is not signed and encrypted using the key whose
   key fingerprint was provided with the MINEX III application.
 * Templates generated are not compliant with ANSI/INCITS 378-2004
   specifications.
 * Templates generated are not compatible for MINEX III black box testing.
 * Library contains symbol names duplicated from NIST code.

Communication
-------------

If you found a bug and can provide steps to reliably reproduce it, or if you
have a feature request, please [open an issue]. Other questions may be addressed
to the [NIST MINEX team].

License
-------

The items in this repository are released in the public domain. See the
[LICENSE] for details.

[MINEX III participation webpage]: https://www.nist.gov/itl/iad/image-group/participation-minex-iii

[`config/`]: https://github.com/usnistgov/minex/tree/master/minexiii/validation/config
[`lib/`]: https://github.com/usnistgov/minex/tree/master/minexiii/validation/lib
[`validate`]: https://github.com/usnistgov/minex/blob/master/minexiii/validation/validate
[`Makefile`]: https://github.com/usnistgov/minex/blob/master/minexiii/validation/Makefile
[`minexiii.h`]: https://github.com/usnistgov/minex/blob/master/minexiii/validation/minexiii.h
[`minexiii_validation.cpp`]: https://github.com/usnistgov/minex/blob/master/minexiii/validation/minexiii_validation.cpp
[`minexiii_validation.h`]: https://github.com/usnistgov/minex/blob/master/minexiii/validation/minexiii_validation.h
[`minexiii_validation_data.h`]: https://github.com/usnistgov/minex/blob/master/minexiii/validation/minexiii_validation_data.h
[`VERSION`]: https://github.com/usnistgov/minex/blob/master/minexiii/validation/VERSION

[Request the validation imagery]:  https://www.nist.gov/itl/iad/image-group/participation-minex-iii

[CentOS vault]: http://vault.centos.org
[🇺🇸 USA]: http://mirror.umd.edu/centos/7.6.1810/isos/x86_64/CentOS-7-x86_64-Everything-1810.iso
[🇪🇺 Europe]: http://centos.mirrors.proxad.net/7.6.1810/isos/x86_64/CentOS-7-x86_64-Everything-1810.iso
[NIST mirror]: http://nigos.nist.gov:8080/evaluations/CentOS-7-x86_64-Everything-1810.iso

[open an issue]: https://github.com/usnistgov/minex/issues
[NIST MINEX team]: mailto:minex@nist.gov

[LICENSE]: https://github.com/usnistgov/minex/blob/master/LICENSE.md
[the MINEX upload form]: https://pages.nist.gov/minex/upload
