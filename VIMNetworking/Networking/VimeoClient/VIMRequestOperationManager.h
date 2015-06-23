//
//  VIMVimeoClient.h
//  VIMNetworking
//
//  Created by Kashif Mohammad on 3/24/13.
//  Copyright (c) 2014-2015 Vimeo (https://vimeo.com)
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#import "AFNetworking.h"
#import "VIMRequestDescriptor.h"
#import "VIMServerResponse.h"

@protocol VIMRequestToken;

@class VIMCache;
@class VIMRequestOperationManager;

typedef void (^VIMRequestCompletionBlock)(VIMServerResponse *response, NSError *error);

extern NSString *const kVimeoClientErrorDomain;
extern NSString *const kVimeoClient_ServiceUnavailableNotification;
extern NSString *const kVimeoClient_InvalidTokenNotification;

@protocol VIMRequestOperationManagerDelegate <NSObject>

@required
- (NSString *)authorizationHeaderValue:(VIMRequestOperationManager *)operationManager;
- (NSString *)acceptHeaderValue:(VIMRequestOperationManager *)operationManager;

@end

@interface VIMRequestOperationManager : AFHTTPRequestOperationManager

@property (nonatomic, weak) id<VIMRequestOperationManagerDelegate> delegate;

@property (nonatomic, strong) VIMCache *cache;

- (id<VIMRequestToken>)requestURI:(NSString *)URI
                  completionBlock:(VIMRequestCompletionBlock)completionBlock;

- (id<VIMRequestToken>)requestDescriptor:(VIMRequestDescriptor *)descriptor
                         completionBlock:(VIMRequestCompletionBlock)completionBlock;

- (id<VIMRequestToken>)requestDescriptor:(VIMRequestDescriptor *)descriptor
                                 handler:(id)handler
                         completionBlock:(VIMRequestCompletionBlock)completionBlock;

- (void)cancelRequest:(id<VIMRequestToken>)request;
- (void)cancelAllRequestsForHandler:(id)handler;
- (void)cancelAllRequests;

NSDictionary *VIMParametersFromQueryString(NSString *queryString);

@end
