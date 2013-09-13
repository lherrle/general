//
//  stackSet.m
//  iStudy
//
//  Created by Laura Herrle on 6/26/13.
//  Copyright (c) 2013 Laura Herrle. All rights reserved.
//

#import "stackSet.h"

@implementation stackSet

- (void) daily: (stack*) d {
    daily = d;
}

- (void) weekly: (stack*) w {
    weekly = w;
}

- (void) monthly: (stack*) m {
    monthly = m;
}

- (void) unused: (stack*) u {
    unused = u;
}

- (void) unusedToDaily: (flashcard*) c {
    flashcard* card = [unused removeCard:c];
    if (card!=nil) [daily addCard:card];
}

- (void) dailyToWeekly: (flashcard*) c {
    flashcard* card = [daily removeCard:c];
    if (card!=nil) [weekly addCard:card];
}

- (void) weeklyToMonthly: (flashcard*) c {
    flashcard* card = [weekly removeCard:c];
    if (card!=nil) [monthly addCard:card];
}

- (void) monthlyToUnused: (flashcard*) c {
    flashcard* card = [monthly removeCard:c];
    if (card!=nil) [unused addCard:card];
}

- (stack*) todaysStack {
    //todo
}

- (stack*) allCards {
    stack* all = [[[daily combine: weekly] combine: monthly] combine: unused];
    return all;
}

@end
