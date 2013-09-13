//
//  stack.m
//  iStudy
//
//  Created by Laura Herrle on 6/25/13.
//  Copyright (c) 2013 Laura Herrle. All rights reserved.
//

#import "stack.h"

@implementation stack

- (void) cards: (NSMutableArray*) c {
    cards = c;
}

- (void) flipFront: (BOOL) f {
    flipFront = f;
}

- (void) current: (int) i {
    current = i;
}

- (BOOL) addCard: (flashcard*) card {
    if(![cards containsObject:card]) {
        [cards addObject:card];
        return true;
    }
    return false;
}

- (stack*) combine: (stack*) s {
    stack* tr = [s copy];
    [tr->cards addObjectsFromArray:self->cards];
    return tr;
}

- (flashcard*) removeCard: (flashcard*) card {
    if([cards containsObject:card]) {
        [cards removeObject:card];
        return card;
    }
    return nil;
}

- (flashcard*) removeFront: (NSString*) front {
    NSEnumerator *enumerator = [cards objectEnumerator];
    flashcard* card;
    
    while (card = (flashcard*)[enumerator nextObject]) {
        if (card.front==front) {
            return card;
        }
    }
    return nil;
}

- (NSString*) showCard {
    if (flipFront) {
        return ((flashcard*)[cards objectAtIndex: current]).front;
    }
    return ((flashcard*)[cards objectAtIndex: current]).back;
}

- (NSString*) flipCurrent {
    if (flipFront) {
        return ((flashcard*)[cards objectAtIndex: current]).back;
    }
    return ((flashcard*)[cards objectAtIndex: current]).front;
    current = (current+1)%([cards count]);
    if (current == 0) {
        NSUInteger count = [cards count];
        for (NSUInteger i = 0; i < count; ++i) {
            // Select a random element between i and end of array to swap with.
            NSInteger nElements = count - i;
            NSInteger n = (arc4random() % nElements) + i;
            [cards exchangeObjectAtIndex:i withObjectAtIndex:n];
        }
    }
}

- (BOOL) checkKeywords: (NSString*) answer {
    BOOL good = true;
    NSEnumerator *enumerator = [((flashcard*)[cards objectAtIndex:current]).keywords objectEnumerator];
    NSString* key;
    
    while (key = (NSString*)[enumerator nextObject]) {
        good = (good && !NSEqualRanges([answer rangeOfString:answer options:NSCaseInsensitiveSearch], NSMakeRange(NSNotFound, 0)));
        
    }
    return good;
}

- (BOOL) checkAnswer: (NSString*) answer {
    return ([((flashcard*)[cards objectAtIndex:current]).front caseInsensitiveCompare:answer]==NSOrderedSame);
}

- (id) init
{
    if ( self = [super init] )
    {
        [self cards:[NSMutableArray arrayWithCapacity:10]];
        [self flipFront: TRUE];
        [self current:0];
    }
    return self;
}

@end
