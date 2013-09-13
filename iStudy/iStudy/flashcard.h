//
//  flashcard.h
//  iStudy
//
//  Created by Laura Herrle on 6/25/13.
//  Copyright (c) 2013 Laura Herrle. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface flashcard : NSObject {
    NSString* front;
    NSString* back;
    NSMutableArray* keywords;
}

- (NSString*) front;
- (NSString*) back;
- (NSMutableArray*) keywords;

- (void) setFront: (NSString*)input;
- (void) setBack: (NSString*)input;
- (void) setKeywords: (NSMutableArray*)keys;

- (BOOL) addKeyword: (NSString*)key;
- (BOOL) removeKeyword: (NSString*)key;
- (BOOL) containsKey: (NSString*)key;

@end
