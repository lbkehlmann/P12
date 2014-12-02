#!/usr/bin/expect

set timeout 20

expect_after {
    timeout {
        puts "----> timeout <----\r"
        exit
    }
}

spawn qemu-system-x86_64 -nographic --serial mon:stdio -hdc kernel/kernel.img -hdd fat439/user.img

expect "username> "
send "user\r"

expect "username> "
send "ender\r"

expect "ender> "
send "shutdown\r"

expect "*** System Shutdown ***\r"
send \001
send "x"