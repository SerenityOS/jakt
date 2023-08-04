# Contributing to Jakt

When contributing to Jakt, make sure that the changes you wish to make are in line with the project direction. If you are not sure about this, open an issue first, so we can discuss it.

Everyone is welcome to work on the project, and while we have lots of fun, it's a serious kind of fun. :^)

## Communication

Join the SerenityOS Discord server: [SerenityOS Discord](https://discord.gg/serenityos). The "Jakt" category of channels is specifically about Jakt and its development.

## Issue policy

Unlike many other software projects, Jakt is not concerned with gaining the largest possible userbase. Its target audience is its own developers. As such, we have limited interest in feature requests from non-contributors.

That said, please do file any bugs you find, keeping the following in mind:

* One issue per bug. Putting multiple things in the same issue makes both discussion and completion unnecessarily complicated.
* No build issues (or other support requests). If the GitHub Actions CI build succeeds, the build problem is most likely on your side. Work it out locally, or ask on Discord.
* Don't comment on issues just to add a joke or irrelevant commentary. Hundreds of people get notified about comments so let's keep them relevant.

## Human language policy

In SerenityOS, we treat human language as seriously as we do programming language.

The following applies to all user-facing strings, code, comments, and commit messages:

* The official project language is American English with ISO 8601 dates and metric units.
* Use proper spelling, grammar, and punctuation.
* Write in an authoritative and technical tone.

Everyone is encouraged to make use of tooling (spell checkers, etc) to make this easier.

## Code submission policy

Nobody is perfect, and sometimes we mess things up. That said, here are some good dos & dont's to try and stick to:

**Do:**

* Conform to the project coding style found in [coding-style.md](https://github.com/SerenityOS/jakt/blob/main/documentation/coding-style.md). Use automatic formatters (`rustfmt`, `clang-format`, etc.) to format code according to project style.
* Choose expressive variable, function and class names. Make it as obvious as possible what the code is doing.
* Split your changes into separate, atomic commits (i.e. A commit per feature or fix, where the build, tests and the system are all functioning).
* Make sure your commits are rebased on the master branch.
* Wrap your commit messages at 72 characters.
* The first line of the commit message is the subject line, and must have the format "Category: Brief description of what's being changed".
* Write the commit message subject line in the imperative mood ("Foo: Change the way dates work", not "Foo: Changed the way dates work").
* Write your commit messages in proper English, with care and punctuation.
* Squash your commits when making revisions after a patch review.
* Add your personal copyright line to files when making substantive changes. (Optional but encouraged!)
* Check the spelling of your code, comments and commit messages.
* If you have images that go along with your code, run `optipng -strip all` on them to optimize and strip away useless metadata - this can reduce file size from multiple kilobytes to a couple hundred bytes.
* If you have sample Jakt files (or outputs) that go along with your changes, please use underscores rather than dashes in the filename (e.g. `my_code_sample.jakt`, not `my-code-sample.jakt`).

**Don't:**

* Submit code that's incompatible with the project licence (2-clause BSD.)
* Touch anything outside the stated scope of the PR.
* Iterate excessively on your design across multiple commits.
* Use weasel-words like "refactor" or "fix" to avoid explaining what's being changed.
* End commit message subject lines with a period.
* Include commented-out code.
* Attempt large architectural changes until you are familiar with the system and have worked on it for a while.
* Engage in excessive "feng shui programming" by moving code around without quantifiable benefit.

## Pull Request Q&A

### I've submitted a PR and it passes CI. When can I expect to get some review feedback?

While unadvertised PRs may get randomly merged by curious maintainers, you will have a much smoother time if you engage with the community on Discord.

### If my PR isn't getting attention, how long should I wait before pinging one of the project maintainers?

Ping them right away if it's something urgent! If it's less urgent, advertise your PR on Discord and ask if someone could review it.

### Who are the project maintainers?

The project maintainers at this time are [@awesomekling](https://github.com/awesomekling), [@jntrnr](https://github.com/jntrnr), [@alimpfard](https://github.com/alimpfard), [@trflynn89](https://github.com/trflynn89), [@AtkinsSJ](https://github.com/AtkinsSJ), and [@ADKaster](https://github.com/ADKaster).

Maintainership is by invitation only and does not correlate with any particular metric.

### Are there specific people to reach out to for different subsystems (e.g. parser, typechecker, runtime, etc)?

In theory, the best person to speak with is whoever wrote most code adjacent to what you're working on. In practice, asking in one of the development channels on Discord is usually easier/better, since that allows many people to join the discussion.

### Is Discord the place to ask for review help, or is Github preferred?

It's definitely better to ask on Discord. Due to the volume of GitHub notifications, many of us turn them off and rely on Discord for learning about review requests.

## Commit Hooks

The repository contains a file called `.pre-commit-config.yaml` that defines several 'commit hooks' that can be run automatically just before and after creating a new commit. These hooks lint your commit message, and the changes it contains to ensure they will pass the automated CI for pull requests.
To enable these hooks firstly follow the installation instructions available at https://pre-commit.com/#install and then enable one or both of the following hooks:
 - pre-commit hook - Runs Meta/lint-ci.sh and Meta/lint-ports.py to ensure changes to the code will pass linting:
   ```console
   pre-commit install
   ```
 - post-commit hook - Lints the commit message to ensure it will pass the commit linting:
   ```console
   pre-commit install --hook-type commit-msg
   ```

## On abandoned pull requests

Sometimes good PRs get abandoned by the author for one reason or another. If the PR is fundamentally good, but the author is not responding to requests, the PR may be manually integrated with minor changes to code and commit messages.

To make this easier, we do appreciate it if folks enable the "Allow edits from maintainers" flag on their pull requests.

## On ideologically motivated changes

This is a purely technical project. As such, it is not an appropriate arena to advertise your personal politics or religious beliefs. Any changes that appear ideologically motivated will be rejected.
