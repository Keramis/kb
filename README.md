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
The encryption isn't real encryption. And, sadly, I can't even null-pad anymore due to the shitty string logic and my own shitty understanding.

Now, integers representing strings are separated by vertical line characters, `'|'`. This is then fed into `kbdecoder`, which just separates the numbers from the vertical lines, and subtracts the given offset that was at the beginning of the line.

Of course, I'll try to update this when possible with possible double or triple null-padding, as to keep the victim (if they find the text file) unaware of the purpose of the text file, as as it is right now with vertical lines separating, it's fairly obvious what's going on.