import os

def test(expr, answ):
	cmd = f'./calc.out \"{expr}\"'
	d = os.popen(cmd).read()

	print(f'{expr} = \n{d}\n\n')
	# print(d)
	assert d == answ+'\n', "Must be \n" + answ

if __name__ == "__main__":
    test("2-4",                                   "-2.000000")
    test("2- -4",                                 "6.000000")
    test("2-+4",                                  "Can't parse string:\n2-+4\n ^\nPlease, check your data!")
    test("2++4",                                  "Can't parse string:\n2++4\n ^\nPlease, check your data!")
    test("2---4",                                 "Can't parse string:\n2---4\n ^\nPlease, check your data!")
    test("2+4*      5",                           "22.000000")
    test("2--4--2",                               "8.000000")
    test("-2",                                    "-2.000000")
    test("1 * 2 * 3 * 4 * 5",                     "120.000000")
    test("1 * 2 * 3 * 4 * 5 / 1 / 2 / 3 / 4 / 5", "1.000000")
    test("1 * 2 / 2 * 3 / 3 * 4 / 4 * 5 / 5",     "1.000000")
    test("2--4*3/2/5 + 7- 23 --2",                "-10.800000")
    test("1/3",                                   "0.333333")
    test("1/-3",                                  "-0.333333")
    test("1//3",                                  "Can't parse string:\n1//3\n ^\nPlease, check your data!")
    test("1/+3",                                  "Can't parse string:\n1/+3\n ^\nPlease, check your data!")
    test("2-4-",                                  "Can't parse string:\n2-4-\n   ^\nPlease, check your data!")    
    test("2*/4",                                  "Can't parse string:\n2*/4\n ^\nPlease, check your data!")
    test("-2*4",                                  "-8.000000")
    test("*2*4",                                  "Can't parse string:\n*2*4\n^\nPlease, check your data!")
    test("**2*4",                                 "Can't parse string:\n**2*4\n ^\nPlease, check your data!")
    test("--2*4",                                 "Can't parse string:\n--2*4\n ^\nPlease, check your data!")
    test("--2**4",                                "Can't parse string:\n--2**4\n   ^\nPlease, check your data!")
    test("2 + 3 * 4 - -2",                        "16.000000")
    test("2 ! 3 ; 4 - -2",                        "Can't parse string:\n2!3;4--2\n ^\nPlease, check your data!")
    