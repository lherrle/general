//
//  stackSet.h
//  iStudy
//
//  Created by Laura Herrle on 6/26/13.
//  Copyright (c) 2013 Laura Herrle. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "stack.h"

@interface stackSet : NSObject {
    stack *daily;
    stack *weekly;
    stack *monthly;
    stack *unused;  // these will be accessed manually instead of on a schedule; where cards go when they are no longer monthly; if gotten wrong go back to daily
    NSCalendarUnit* weekday;
    NSCalendarUnit* monthdate;
}

- (void) daily: (stack*) d;
- (void) weekly: (stack*) w;
- (void) monthly: (stack*) m;
- (void) unused: (stack*) u;

- (void) unusedToDaily: (flashcard*) c;
- (void) dailyToWeekly: (flashcard*) c;
- (void) weeklyToMonthly: (flashcard*) c;
- (void) monthlyToUnused: (flashcard*) c;

- (stack*) todaysStack;

- (stack*) allCards;

@end
