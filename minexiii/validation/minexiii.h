/*
 * This software was developed at the National Institute of Standards and
 * Technology (NIST) by employees of the Federal Government in the course
 * of their official duties.  Pursuant to title 17 Section 105 of the
 * United States Code, this software is not subject to copyright protection
 * and is in the public domain.  NIST assumes no responsibility whatsoever for
 * its use by other parties, and makes no guarantees, expressed or implied,
 * about its quality, reliability, or any other characteristic.
 */

#ifndef MINEX_III_H_
#define MINEX_III_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * MINEX III API.
 * Backwards compatible to Ongoing MINEX.
 */

/**
 * @brief
 * Obtain CBEFF PID information.
 *
 * @param[out] template_generator
 * PID that identifies the participant's template generator.
 * @param[out] template_matcher
 * PID that identifies the participant's template matcher.
 *
 * @return
 * MINEX_RET_SUCCESS.
 */
int32_t
get_pids(
    uint32_t *template_generator,
    uint32_t *template_matcher);

/**
 * @brief
 * Create a fingerprint template from a raw image.
 *
 * @param[in] raw_image
 * Uncompressed image data.
 * @param[in] finger_quality
 * Quality of fingeprint depicted in raw_image, from MINEXQuality.
 * @param[in] finger_position
 * Position of the fingerprint depicted in raw_image, from MINEXFingerPositon.
 * @param[in] impression_type
 * Impression of the finger depicted in raw_image, from MINEXImpressionType.
 * @param[in] height
 * Number of rows in raw_image.
 * @param[in] width
 * Number of columns in raw_image.
 * @param[in,out] output_template
 * A pre-allocated memory location of MINEX_MAX_TEMPLATE_SIZE-bytes where
 * template should be stored.
 *
 * @return
 * MINEX_RET_SUCCESS on success, or other MINEXReturnCode integer on failure.
 *
 * @note
 * Even if unsuccessful, output_template must be set to a valid MINEX-style
 * template with a single finger view and zero minutiae.
 */
int32_t
create_template(
    const uint8_t *raw_image,
    const uint8_t finger_quality,
    const uint8_t finger_position,
    const uint8_t impression_type,
    const uint16_t height,
    const uint16_t width,
    uint8_t *output_template);

/**
 * @brief
 * Compare two fingerprint templates, as returned from create_template().
 *
 * @param[in] verification_template
 * A template returned from create_template(), though not necessarily this
 * software library's implementation.
 * @param[in] enrollment_template
 * A template returned from create_template(), though not necessarily this
 * software library's implementation.
 * @param[out] similarity
 * A similarity score representing verification_templates similarity to
 * enrollment_template
 *
 * @return
 * MINEX_RET_SUCCESS on success, or other ReturnCode integer on failure.
 */
int32_t
match_templates(
    const uint8_t *verification_template,
    const uint8_t *enrollment_template,
    float *similarity);

/*
 * Types.
 */

/** Values to indicate the return status of a MINEX API function. */
typedef enum {
	/** Success. */
	MINEX_RET_SUCCESS = 0,
	/** Image size is unsupported. */
	MINEX_RET_BAD_IMAGE_SIZE = 1,
	/** Failed for unspecified reason. */
	MINEX_RET_FAILURE_UNSPECIFIED = 2,
	/** Impression type not supported. */
	MINEX_RET_FAILURE_BAD_IMPRESSION = 3,
	/** Received a template without minutia. */
	MINEX_RET_FAILURE_NULL_TEMPLATE = 4,
	/** Verification template is bad. */
	MINEX_RET_FAILURE_BAD_VERIFICATION_TEMPLATE = 5,
	/** Enrollment template is bad. */
	MINEX_RET_FAILURE_BAD_ENROLLMENT_TEMPLATE = 6
} MINEXReturnCode;

/** Fingerprint impression types. */
typedef enum
{
	/** Live-scan, plain. */
	MINEX_IMP_LIVESCAN_PLAIN = 0,
	/** Non live-scan, plain. */
	MINEX_IMP_NONLIVESCAN_PLAIN = 2
} MINEXImpressionType;

/** Finger positions. */
typedef enum {
	/** Unknown or unspecified position. */
	MINEX_FINGER_UNKNOWN = 0,
	/** Right thumb. */
	MINEX_FINGER_RIGHT_THUMB = 1,
	/** Right index. */
	MINEX_FINGER_RIGHT_INDEX = 2,
	/** Right middle. */
	MINEX_FINGER_RIGHT_MIDDLE = 3,
	/** Right ring. */
	MINEX_FINGER_RIGHT_RING = 4,
	/** Right little. */
	MINEX_FINGER_RIGHT_LITTLE = 5,
	/** Left thumb. */
	MINEX_FINGER_LEFT_THUMB = 6,
	/** Left index. */
	MINEX_FINGER_LEFT_INDEX = 7,
	/** Left middle. */
	MINEX_FINGER_LEFT_MIDDLE = 8,
	/** Left ring. */
	MINEX_FINGER_LEFT_RING = 9,
	/** Left little. */
	MINEX_FINGER_LEFT_LITTLE = 10
} MINEXFingerPosition;

/** Quality values. */
typedef enum {
	/** Equivalent to NFIQ 5. */
	MINEX_QUALITY_POOR = 20,
	/** Equivalent to NFIQ 4. */
	MINEX_QUALITY_FAIR = 40,
	/** Equivalent to NFIQ 3. */
	MINEX_QUALITY_GOOD = 60,
	/** Equivalent to NFIQ 2. */
	MINEX_QUALITY_VERYGOOD = 80,
	/** Equivalent to NFIQ 1. */
	MINEX_QUALITY_EXCELLENT = 100
} MINEXQuality;

/*
 * Useful constants.
 */

/** Vertical and horizontal resolutions of raw_image in create_template(). */
static const uint16_t MINEX_IMAGE_PPI = 500;
/** Minimum width of raw_image in create_template(). */
static const uint16_t MINEX_MIN_IMAGE_WIDTH = 150;
/** Maximum width of raw_image in create_template(). */
static const uint16_t MINEX_MAX_IMAGE_WIDTH = 812;
/** Minimum height of raw_image in create_template(). */
static const uint16_t MINEX_MIN_IMAGE_HEIGHT = 166;
/** Maximum height of raw_image in create_template(). */
static const uint16_t MINEX_MAX_IMAGE_HEIGHT = 1000;

/** Minimum size of a MINEX-compliant template. */
static const uint16_t MINEX_MIN_TEMPLATE_SIZE = 32;
/** Maximum size of a MINEX-compliant template. */
static const uint16_t MINEX_MAX_TEMPLATE_SIZE = 800;
/** Maximum number of minutiae */
static const uint8_t MINEX_MAX_MINUTIAE = 128;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MINEX_III_H_ */

