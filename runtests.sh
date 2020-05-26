#!/bin/bash
for i in {1..10}
do
  ./checkpack < test$i.in > tmp.svg
  cmp tmp.svg test$i.svg
done
rm -r tmp.svg
