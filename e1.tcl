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
send "ls\r"

expect "ender> "
send "cat test1.txt\r"

expect "ender> "
send "chuser\r"

expect "username> "
send "admin\r"

expect "admin> "
send "users.txt\r"

expect "admin> "
send "chuser\r"

expect "username> "
send "peter\r"

expect "peter> "
send "test0.txt\r"

expect "peter> "
send "shutdown\r"

expect "*** System Shutdown ***\r"
send \001
send "x"