#!/bin/bash
tmp="`pwd`/$0"
bundle=`dirname "$tmp"`
exec "$bundle/../Resources/bin/minetest"
