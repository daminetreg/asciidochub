
# asciidochub
Import Github Issues as Asciidoc into asciidoc documents

Simply include the issues you need with the special syntax include directive:

```
include::user/repo#3[]
```

It will include in your Asciidoc document the issue number **3** of the repo at github.com/user/repo.

It also work with Github Enterprise instances if you paas the github enterprise url to the tool.

# How to use
First install kramdown-asciidoc:
```
sudo gem install kramdown-asciidoc
```

Then simply run :
```
nxxm . -t gcc-7-cxx17
build/gcc-7-cxx17/bin/asciidochub <path-to-asciidoc.adoc> [<gh-enterprise-api-url>]
```

## License
This code is under the GPLv3 don’t hesitate to contact me if you need another license.
See [LICENSE](./LICENSE)


