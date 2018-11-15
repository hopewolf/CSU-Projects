Command line invocation:
machine> java HW6 2 5 10 5

Output:
Producer: Inserted integer 16 at Location 0 at instant: 2017/11/17 13:22:59:00261
Consumer 2: Removed 16 from location: 0 at Time: 2017/11/17 13:22:59:00263
Producer: Inserted integer 62 at Location 1 at instant: 2017/11/17 13:22:59:00264
Consumer 2: Removed 62 from location: 1 at Time: 2017/11/17 13:22:59:00264
Producer: Inserted integer 26 at Location 2 at instant: 2017/11/17 13:22:59:00264
Consumer 1: Removed 26 from location: 2 at Time: 2017/11/17 13:22:59:00264
Producer: Inserted integer 59 at Location 3 at instant: 2017/11/17 13:22:59:00265
Consumer 2: Removed 59 from location: 3 at Time: 2017/11/17 13:22:59:00265
Producer: Inserted integer 27 at Location 4 at instant: 2017/11/17 13:22:59:00265
Consumer 1: Removed 27 from location: 4 at Time: 2017/11/17 13:22:59:00265
Producer: Inserted integer 5 at Location 0 at instant: 2017/11/17 13:22:59:00266
Consumer 2: Removed 5 from location: 0 at Time: 2017/11/17 13:22:59:00266
Producer: Inserted integer 76 at Location 1 at instant: 2017/11/17 13:22:59:00266
Consumer 1: Removed 76 from location: 1 at Time: 2017/11/17 13:22:59:00267
Producer: Inserted integer 95 at Location 2 at instant: 2017/11/17 13:22:59:00267
Consumer 2: Removed 95 from location: 2 at Time: 2017/11/17 13:22:59:00267
Producer: Inserted integer 11 at Location 3 at instant: 2017/11/17 13:22:59:00267
Consumer 1: Removed 11 from location: 3 at Time: 2017/11/17 13:22:59:00268
Producer: Inserted integer 66 at Location 4 at instant: 2017/11/17 13:22:59:00268
Consumer 2: Removed 66 from location: 4 at Time: 2017/11/17 13:22:59:00268
Producer: Done producing 10 items. Sum of numbers generated: 443
Consumer 2 Unable to consume, buffer empty, at Time: 2017/11/17 13:22:59:00269
Consumer 2: exiting after waiting for 15 Sum of numbers consumed: 303
Consumer 1 Unable to consume, buffer empty, at Time: 2017/11/17 13:22:59:00269
Consumer 1: exiting after waiting for 15 Sum of numbers consumed: 140
