//
//  flashcard.m
//  iStudy
//
//  Created by Laura Herrle on 6/25/13.
//  Copyright (c) 2013 Laura Herrle. All rights reserved.
//

#import "flashcard.h"

@implementation flashcard

- (NSString*) front {
    return front;
}

- (NSString*) back {
    return back;
}

- (NSMutableArray*) keywords {
    return keywords;
}

- (void) setFront: (NSString*)input {
    front = input;
}

- (void) setBack: (NSString*)input {
    back = input;
}

- (void) setKeywords:(NSMutableArray *)keys {
    keywords = keys;
}

- (BOOL) addKeyword:(NSString *)key {
    if (![keywords containsObject:key]) {
        [keywords addObject:key];
        return true;
    }
    return false;
}

- (BOOL) removeKeyword:(NSString *)key {
    if ([keywords containsObject:key]) {
        [keywords removeObject:key];
        return true;
    }
    return false;
}

- (BOOL) containsKey:(NSString *)key {
    return [keywords containsObject:key];
}

- (id) init
{
    if ( self = [super init] )
    {
        [self setFront:@"Empty"];
        [self setBack:@"Empty"];
        [self setKeywords:[NSMutableArray arrayWithCapacity:10]];
    }
    return self;
}

@end
