Placement Density Function Grid Detector
========================================

A tool for detecting periodic (e.g., "grid") structures in minutia placement
density functions.

About Placement Density Functions
---------------------------------

Placement density functions, or "density plots," show where a fingerprint
minutia extraction algorithm, or "template generator," tends to find minutia in
fingerprint images. They are two-dimensional histograms where the degree of
illumination at a coordinate indicates how frequently the extraction algorithm
located a minutiae point at that location. The purpose of showing minutia
density plots is to determine whether a template generator exhibits a regional
preference when locating minutia.

Periodic structures and other regional preferences are an indication that the
template generator is departing from the minutiae placement requirements of
ANSI/INCITS 378-2004, clause 5. The expected pattern is a locally uniform
distribution, and the appearance of local structure indicates non-conformance
with the standard.

About This Tool
---------------

This tool establishes a closed-form test for *some* forms of high frequency
periodic structure in minutia density plots by searching for modulation in the
plot's Fourier representation. Periodic structure is defined to exist if the
maximum modulation is greater than or equal to **0.002**. This value was
selected empirically so that decisions agree with *most* manual inspection
results.

For [MINEX III](
https://www.nist.gov/itl/iad/image-group/minutiae-interoperability-exchange-minex-iii),
this tool is a first pass at detecting periodic structure. A test administrator
may still override the tool's decision if the minutia density plot features
other structure judged to be non-compliant with ANSI/INCITS 378-2004, clause 5.
While it depends on an empirical threshold, we consider this method superior to
the old procedure of human inspection.

Requirements
------------

This script requires [R](https://www.r-project.org), and was created with R
3.2.5. To read PNG images, use of the free R package [png 0.1-7](
https://cran.r-project.org/web/packages/png/index.html) is required.

Usage
-----

    # Run from a from a square 8-bit PNG minutia image
    minexiii_grid_detector <minutia_density.png>

    # Run from a x,y,density CSV histogram
    minexiii_grid_detector <x_y_count.csv> <square dimension>

Example
-------

*Example minutia density images can be found on the [MINEX III
results webpage](http://nigos.nist.gov:8080/evaluations/minexiii/density).*

    $ minexiii_grid_detector minutia_density.csv 368
       File: minutia_density.csv
    Pattern: TRUE
      Score: 0.00294

    $ minexiii_grid_detector minutia_density.png
       File: minutia_density.png
    Pattern: FALSE
      Score: 0.00084

This script contains a function (`display.fft`) to display the Fourier
transform, but it is commented out by default.

Communication
-------------

If you found a bug and can provide steps to reliably reproduce it, or if you
have a feature request, please
[open an issue](https://github.com/usnistgov/minex/issues). Other
questions may be addressed to the [NIST MINEX team](mailto:minex@nist.gov).

License
-------

The items in this repository are released in the public domain. See the
[LICENSE](https://github.com/usnistgov/minex/blob/master/LICENSE.md)
for details.
