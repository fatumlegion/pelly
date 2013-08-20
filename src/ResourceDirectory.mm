#include "ResourceDirectory.hpp"
#import <Foundation/Foundation.h>

std::string getRPath(void) {
    // Get the resources dir path.
	std::string rpath;
	NSBundle* bundle = [NSBundle mainBundle];
	if (bundle == nil) {
		NSLog(@"bundle is nil... thus no resources path can be found.");
	} else {
		NSString* path = [bundle resourcePath];
		rpath = [path UTF8String] + std::string("/");
	}
    
    return rpath;
}