//
//  Header.h
//  MicroBlinkDev
//
//  Created by Jura Skrlec on 14/12/2017.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@protocol MBOcrRecognizerRunnerViewDelegate;
@protocol MBDetectionRecognizerRunnerViewDelegate;
@protocol MBScanningRecognizerRunnerViewDelegate;
@protocol MBRecognizerRunnerViewControllerDelegate;
@protocol MBDebugRecognizerRunnerViewDelegate;

@class MBSettings;
@class MBOverlayViewController;

NS_ASSUME_NONNULL_BEGIN

/**
 * Protocol for View controllers which present camera and provide scanning features
 */
@protocol MBRecognizerRunnerViewController <NSObject>

@property (nonatomic, weak) MBOverlayViewController<MBOcrRecognizerRunnerViewDelegate> * ocrRecognizerRunnerViewDelegate;
@property (nonatomic, weak) MBOverlayViewController<MBDetectionRecognizerRunnerViewDelegate> *detectionRecognizerRunnerViewDelegate;
@property (nonatomic, weak) MBOverlayViewController<MBScanningRecognizerRunnerViewDelegate> *scanningRecognizerRunnerViewDelegate;
@property (nonatomic, weak) MBOverlayViewController<MBRecognizerRunnerViewControllerDelegate> *recognizerRunnerViewControllerDelegate;
@property (nonatomic, weak) MBOverlayViewController<MBDebugRecognizerRunnerViewDelegate> *debugRecognizerRunnerViewDelegate;

/**
 * Scanning region
 * Defines a portion of the screen in which the scanning will be performed.
 * Given as a CGRect with unit coordinating system:
 *
 * @example CGRectMake(0.2f, 0.5f, 0.4f, 0.3f) defines a portion of the screen which starts at
 *   20% from the left border
 *   50% from the top
 *   covers 40% of screen width
 *   and 30% of screen heeight
 */
@property (nonatomic) CGRect scanningRegion;

/**
 * MBRecognizerRunnerViewController's shouldAutorotate will return this value.
 *
 * Default: NO.
 *
 * Set it to YES if you want scanning view controller to autorotate.
 */
@property (nonatomic) BOOL autorotate;

/**
 * MBRecognizerRunnerViewController's supportedInterfaceOrientations will return this value.
 *
 * Default: UIInterfaceOrientationMaskPortrait.
 */
@property (nonatomic) UIInterfaceOrientationMask supportedOrientations;

/**
 * MBRecognizerRunnerViewController' settings will return this value.
 */
@property (nonatomic) MBSettings *settings;

/**
 * Pause scanning without dismissing the camera view.
 *
 * If there is camera frame being processed at a time, the processing will finish, but the results of processing
 * will not be returned.
 *
 * @warning must be called from Main thread to ensure thread synchronization
 */
- (BOOL)pauseScanning;

/**
 * Retrieve the current state of scanning.
 *
 *  @return YES if scanning is paused. NO if it's in progress
 *
 *  @warning must be called from Main thread to ensure thread synchronization
 */
- (BOOL)isScanningPaused;

/**
 * Resumes scanning. Optionally, internal state of recognizers can be reset in the process.
 *
 * If you continue scanning the same object, for example, the same slip, or the same MRTD document, to get result
 * with higher confidence, then pass NO to reset State.
 *
 * If you move to scan another object, for example, another barcode, or another payment slip, then pass YES to reset State.
 *
 * Internal state is used to use the fact that the same object exists on multiple consecutive frames, and using internal
 * state provides better scanning results.
 *
 *  @param resetState YES if state should be reset.
 *
 *  @warning must be called from Main thread to ensure thread synchronization
 */
- (BOOL)resumeScanningAndResetState:(BOOL)resetState;

/**
 * Resumes camera session. This method is automatically called in viewWillAppear when ScanningViewController enters screen.
 */
- (BOOL)resumeCamera;

/**
 * Pauses camera session. This method is automatically called in viewDidDissapear when ScanningViewController exits screen.
 */
- (BOOL)pauseCamera;

/**
 * Retrieve the current state of camera.
 *
 *  @return YES if camera is paused. NO if camera is active
 */
- (BOOL)isCameraPaused;

/**
 * Play scan sound.
 *
 * It uses default scan sound, you can change it by setting your own soundFilePath in PPUiSettings.
 */
- (void)playScanSuccesSound;

/**
 * Call to turn on torch without camera overlay
 */
- (void)willSetTorchOn:(BOOL)torchOn;

/**-------------------------------*/
/** @name Settings recofiguration */
/**-------------------------------*/
- (void)resetState;

/**
 * Method which is used to apply MBSettings object given by currentSettings property
 *
 * Usual use case is to update settings on the fly, to perform some complex scanning functionality
 * where a reconfiguration of the recognizers is needed.
 */
- (void)applySettings:(MBSettings *)newSettings;

@end

NS_ASSUME_NONNULL_END
