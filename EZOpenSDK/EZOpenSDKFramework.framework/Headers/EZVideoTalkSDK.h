//
//  EZVideoTalkSDK.h
//  EZOpenSDK
//
//  Created by yuqian on 2020/3/14.
//  Copyright © 2020 Hikvision. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "EZVideoTalkParam.h"

NS_ASSUME_NONNULL_BEGIN

typedef enum : NSUInteger {
    EZVideoTalkMessageUnkown,
    EZVideoTalkMessageRoomCreated,      //创建房间成功
    EZVideoTalkMessagePeerEnteredRoom,  //目前未使用，用于多方
    EZVideoTalkMessagePeerLeaveRoom,    //目前未使用，用于多方
    EZVideoTalkMessageStartInputData    //链接建立成功，开始推流
} EZVideoTalkMessageType;


@class EZVideoTalkSDK;

@protocol EZVideoTalkSDKDelegate<NSObject>

- (void)videoTalk:(EZVideoTalkSDK *)client didReceivedError:(int32_t)errorCode;

/**
 回调消息

 @param client client
 @param messageCode 消息码
 @param msg 透传消息
 */
- (void)videoTalk:(EZVideoTalkSDK *)client didReceivedMessage:(EZVideoTalkMessageType)messageType msg:(NSString*)msg;

/**
 回调消息 bavclient log回调
 
 @param client client
 @param msg 透传消息
 */
- (void)videoTalk:(EZVideoTalkSDK *)client didReceivedBavClientLogMsg:(NSString*)msg;

/**
 显示回调，首次画面出来以及后续画面尺寸发生变化时回调

 @param client client
 @param width 画面宽度
 @param height 画面高度
 */
- (void)videoTalk:(EZVideoTalkSDK *)clientt didDisplayWidth:(int32_t)width height:(int32_t)height;

/**
 播放卡顿
 
 @param client client
 @param delayTime 卡顿时间
 */
- (void)videoTalk:(EZVideoTalkSDK *)client playDelayTime:(int32_t)delayTime;

/**
 播放卡顿统计
 
 @param client client
 @param delayTimeStat 卡顿时间
 */
- (void)videoTalk:(EZVideoTalkSDK *)client playDelayTimeStatistics:(double)delayTimeStat;

@end

@interface EZVideoTalkSDK : NSObject

@property (nonatomic, assign, readonly) int32_t roomID;
@property (nonatomic, weak) id<EZVideoTalkSDKDelegate> delegate;

#pragma mark - SDK
/**
SDK初始化

 @param param 必填 配置参数
 @param localWin 本地窗口
 @param remoteWin 远端窗口
 
 @return 返回值
 */
- (instancetype)initWithParam:(EZVideoTalkParam *)param
                  localWindow:(UIView *)localWin
                 remoteWindow:(UIView *)remoteWin;

/**
 开始双向音视频对讲，耗时接口
 */
- (void)start;

/**
 停止双向音视频对讲
 */
- (void)stop;

#pragma mark - 日志调试
/**
 日志设置
 
 @param enable 是否打印日志
 @param logCallback 日志回调，上层自定义处理
 */
+ (void)setDebugLogEnable:(BOOL)enable withLogCallback:(void(^)(NSString *logStr))logCallback;

/**
 打开对端码流抓取

 @param enble 是否打开
 */
+(void)setDebugVideoLog:(BOOL)enble;

/**
 获取sdk版本信息

 @return 版本号
 */
+ (NSString*)getVersion;

@end

NS_ASSUME_NONNULL_END
