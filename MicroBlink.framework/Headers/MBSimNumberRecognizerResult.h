//
//  MBSimNumberRecognizerResult.h
//  MicroBlinkDev
//
//  Created by Jura Skrlec on 21/11/2017.
//

#import <Foundation/Foundation.h>
#import "MBMicroblinkDefines.h"
#import "MBRecognizerResult.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Recognizer that can perform recognition of barcodes on SIM packaging.
 */
PP_CLASS_DEPRECATED_IOS(1.0, 7.0, "MBSimNumberRecognizerResult is deprecated in PDF417 SDK 7.0.0")
@interface MBSimNumberRecognizerResult : MBRecognizerResult<NSCopying>

MB_INIT_UNAVAILABLE

/**
 * Returns the recognized SIM number from barcode or empty string if recognition failed.
 */

@property (nonatomic, nullable, strong, readonly) NSString *simNumber;

@end

NS_ASSUME_NONNULL_END
