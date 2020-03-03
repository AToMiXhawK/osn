# Message Queue with Priority

compile seperately and execute simultaneously

use `-lrt` flag for `mq_open`, `mq_send`, etc.. to work 

eg: 

`gcc send.c -o send.out -lrt`

`gcc rec.c -o rec.out -lrt`

open two terminal instances,

in first one: `./send.out`

in second one: `./rec.out`