## Disclaimer:

---

This, and all contents of this project are made for __educational__ purposes only, and any malicious use of this tool are not permitted by me, the project creator. Of course, I cannot stop you acting malicously, but this is not a good-enough tool to use for serious malicious purposes, so I suggest going somewhere else if you need any "dark" services.

---

# What is this?
This is /kb, standing for [keyboard]. This is (was?) my humble attempt at a keylogger, employing basic methods of hooking via `SetWindowsHookExA`, keystroke monitoring with special-character support, and a (sort-of advanced) string detection method which looks for `backspace`, `enter`, and `tab` keys.

If these features are not currently in the project, that's because they haven't been implemented yet, and I'm still working on them.

---

## Contents
The contents of this repository are self-contained, meaning that everything (hopefully) should be included in the source code above, apart from the standard C++ libraries that I have access through Visual Studio (such as `Windows.h`, `iostream`, `string`, etc).

The first project, `kb`, is the meat and potatoes of the keylogger, so to speak. It does the logging, the monitoring, and the sending of said kelogger to a desired location (I'm thinking of using a discord webhook, but I have not thought about this just yet; how the text contents will extract).

The second project, `kbdecoder`, is used for inputting the encoded text document into it, and getting the characters out.

---

## The ""encryption""
The encryption isn't really encryption, since it can be reverse-engineered with minimal effort on the user's end. All it does is null-pad lines in a text document, along with offsetting them by a random number that is determined at the line creation based on `mersenne twister` and the current `tick count`.

Here's an example string: `7012060053019005308`

Decoding this string is fairly simple. The number at the beginning (which can't be a 0, it has to be an integer from 1-9), represents the `offset` that each character in the string will have. The numbers in-between the zeroes are the integer representations of said characters, casted by default simply with `(int)ch`, `ch` being the character.

Splitting up the string we get:

`7 0 12 0 60 0 53 0 190 0 53 0 8`

Keep in mind that the zeroes are not characters, but are there to put "spaces" in-between the characters, just to make the victim second-guess what this text document is, if they ever find it. I understand that this is not roubst encryption, but this is not a robust keylogger, so if you want to act maliciously, refer to the disclaimer at the top.

Anyways, to decode the string, all we have to do is subtract `7` from each integer here, which would give us the completed string.