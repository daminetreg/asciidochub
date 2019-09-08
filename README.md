# asciidochub
Import Github Issues as Asciidoc into asciidoc documents

Simply include the issues you need with the special syntax include directive:

```
include::user/repo#3[]
```

It will include in your Asciidoc document the issue number **3** of the repo at github.com/user/repo.

It also work with Github Enterprise instances if you pass the github enterprise url to the tool.

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

## Authenticating for private repositories
To authenticate on private or github enterprise repositories export `GH_USER` and `GH_PASS` as environment variable. If you have enabled 2FA, you should generate a developer Personal Access Token with "repo" scope.

```shell
export GH_USER=username
export GH_PASS=personal-access-token
```


## License
This code is under the GPLv3 don’t hesitate to contact me if you need another license.
See [LICENSE](./LICENSE)


