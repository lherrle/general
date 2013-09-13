//
//  stack.h
//  iStudy
//
//  Created by Laura Herrle on 6/25/13.
//  Copyright (c) 2013 Laura Herrle. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "flashcard.h"

@interface stack : NSObject {
    NSMutableArray* cards;
    BOOL flipFront;
    int current;
}

- (void) cards: (NSMutableArray*) c;
- (void) flipFront: (BOOL) f;
- (void) current: (int) i;

- (BOOL) addCard: (flashcard*) card;
- (stack*) combine: (stack*) s;
- (flashcard*) removeCard: (flashcard*) card; // or front?
- (flashcard*) removeFront: (NSString*) front;
- (NSString*) showCard;
- (NSString*) flipCurrent;
- (BOOL) checkKeywords: (NSString*) answer;
- (BOOL) checkAnswer: (NSString*) answer;

@end
