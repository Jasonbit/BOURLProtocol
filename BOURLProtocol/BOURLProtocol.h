//
//  BOURLProtocol.h
//  
//
//  Created by Boris Charpentier on 02/10/13.
//  Copyright (c) 2013 Boris Charpentier. All rights reserved.
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

/**
    The purpose of this method is to simplify mocking with AFNetworking
 */

#import <Foundation/Foundation.h>

typedef void(^BOURLProtocolBlock)(NSURLProtocol *protocol, NSURLRequest *request);

@interface BOURLProtocol : NSURLProtocol <NSURLConnectionDelegate, NSURLConnectionDataDelegate>

/*****************************************************************************/
#pragma mark - Initialisation
/**
 Use this method to activate the usage of the protocol
 Never forget to desactivate it (see unregisterSpecialProtocol
 */
+ (void)registerSpecialProtocol;

/**
 Desactivate protocol and remove all stubs.
 
 */
+ (void)unregisterSpecialProtocol;

/*****************************************************************************/
#pragma mark - Stubs Methods

/**
 Use this method to load another url when a Path is called like : 
 [BOURLProtocol stubPath:@"/categories" load:[[NSBundle bundleForClass:[self class]] URLForResource:@"categories" withExtension:@"json"]];
 The default MIMETYPE is @"application/json"
 The default encoding is @"UTF8"
 
 @param path, NSString, the relative path of the url you want to mock
 @param url, NSURL, url, local or distant, call in place of the path.
 
 @return void
 */

+ (void)stubPath:(NSString *)path load:(NSURL *)url;

/**
 This is the same as stubPath:load: with expected MIMETYPE configuration.
 Use this method to load another url when a Path is called like :
 [BOURLProtocol stubPath:@"/categories" mimeType:@"application/json" load:[[NSBundle bundleForClass:[self class]] URLForResource:@"categories" withExtension:@"json"]];
 The default encoding is @"UTF8"
 
 @param path, NSString, the relative path of the url you want to mock
 @param mimeType, NSStrng, the mimeType a normal orperation(or not), should have return.
 @param url, NSURL, url, local or distant, call in place of the path.
 
 */
+ (void)stubPath:(NSString *)path mimeType:(NSString *)mimeType load:(NSURL *)url;

/**
 This is the same as stubPath:mimeType:load: with specific request query in complement of Path to determine if the call should be mock
 Use this method to load another url when a Path is called like :
 [BOURLProtocol stubPath:@"/categories" parameters:@{@"page":@"1",@"authentication_token":@"TEST"} mimeType:@"application/json" load:[[NSBundle bundleForClass:[self class]] URLForResource:@"categories" withExtension:@"json"]];
 The default encoding is @"UTF8"
 
 @param path, NSString, the relative path of the url you want to mock
 @param params, NSDictionary, the query for a specific path
 @param mimeType, NSStrng, the mimeType a normal orperation(or not), should have return.
 @param url, NSURL, url, local or distant, call in place of the path.

 /!\ BEWARE /!\ ALL KEY AND VALUE IN PARAMS SHOULD BE NSSTRING.
 This feature seems to not always work correctly in CI this is why it is commented
 Next version would hopefully fix it
 + (void)stubPath:(NSString *)path parameters:(NSDictionary *)params mimeType:(NSString *)mimeType load:(NSURL *)url;
*/
 
/**
 Use this to return data directly.
 The default MIMETYPE is @"application/json"
 The default encoding is @"UTF8"
 
 @param path, NSString, the relative path of the url you want to mock
 @param data, NSData, data use for the connection response
 
 */
+ (void)stubPath:(NSString *)path withData:(NSData *)data;
/**
 Use this to simulate an error, for a specific Path you can return an NSError.
 
 @param path, NSString, the relative path of the url
 @param error, NSError, the error to return
 
 */

+ (void)stubPath:(NSString *)path fail:(NSError *)error;
/**
 Use this to fully custom what you want, you get the NSURLProtocol instance, and the request, it's up to you to do what you want.
 
 @param path, NSString, the relative path of the url you want to mock
 @param block, BOURLProtocolBlock, the block to execute 

 */
+ (void)stubPath:(NSString *)path execute:(BOURLProtocolBlock)block;


/*****************************************************************************/
#pragma mark - Utils

/**
 Remove a specific stub for a path.
 The unregister method remove all.
 */
+ (void)removeStubForPath:(NSString *)path;

@end
