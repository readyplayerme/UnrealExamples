# Welcome to the Ready Player Me Unreal SDK contributing guide

Thank you for investing your time in contributing to our project! Any contribution you make will be reflected on [https://github.com/readyplayerme/rpm-unreal-web-browser](https://github.com/readyplayerme/rpm-unreal-web-browser) :sparkles:. 

Read our [Code of Conduct](./CODE_OF_CONDUCT.md) to keep our community approachable and respectable.

In this guide you will get an overview of the contribution workflow from opening an issue, creating a PR, reviewing, and merging the PR.

Use the table of contents icon on the top left corner of this document to get to a specific section of this guide quickly.


## New contributor guide

To get an overview of the project, read the [README](README.md). Here are some resources to help you get started with open source contributions:

- [FAQ](#faq)
- [Set up Git](https://docs.github.com/en/get-started/quickstart/set-up-git)
- [GitHub flow](https://docs.github.com/en/get-started/quickstart/github-flow)
- [Collaborating with pull requests](https://docs.github.com/en/github/collaborating-with-pull-requests)


## FAQ

#### **Did you find a bug?**

* **Ensure the bug was not already reported** by searching on GitHub under [Issues](https://github.com/readyplayerme/rpm-unreal-web-browser/issues).

* If you're unable to find an open issue addressing the problem, [open a new one](https://github.com/readyplayerme/rpm-unreal-web-browser/issues/new). Be sure to include a **title and clear description**, as much relevant information as possible, and a **code sample** or an **executable test case** demonstrating the expected behavior that is not occurring.

* If possible, use the relevant bug report templates to create the issue. Simply copy the content of the appropriate template into a .rb file, make the necessary changes to demonstrate the issue, and **paste the content into the issue description**:
  * [**Generic template** for other issues](https://github.com/readyplayerme/rpm-unreal-sdk/blob/develop/.github/pull_request_template.md)

* If you would like to contact us directly to report an issue or for general support requests contact our Ready Player Me Support email [support@readyplayer.me](mailto:support@readyplayer.me).

#### **Did you write a patch that fixes a bug?**

* Open a new GitHub pull request with the patch.

* Ensure the PR description clearly describes the problem and solution. Include the relevant issue number if applicable.

* Before submitting, please read the [Contributing to Ready Player Me Web Browser](#) guide to know more about our coding conventions and best practices.

#### **Did you fix whitespace, format code, or make a purely cosmetic patch?**

Changes that are cosmetic in nature and do not add anything substantial to the stability, functionality, or testability will generally not be accepted.

#### **Do you intend to add a new feature or change an existing one?**

* Suggest your change to the Ready Player Me support email [support@readyplayer.me](mailto:support@readyplayer.me) and start writing code.

* **Do not open an issue on GitHub** until you have collected positive feedback about the change. GitHub issues are primarily intended for bug reports and fixes.

#### **Do you have questions about the source code?**

* Ask any question about how to use the Ready Player Me Web Browser in the [Ready Player Me support email](mailto:support@readyplayer.me).

## Issues

#### Create a new issue

If you spot a problem with the docs, [search if an issue already exists](https://docs.github.com/en/github/searching-for-information-on-github/searching-on-github/searching-issues-and-pull-requests#search-by-the-title-body-or-comments). If a related issue doesn't exist, you can open a new issue using a relevant [issue form](https://github.com/github/docs/issues/new/choose). 

#### Solve an issue

Scan through our [existing issues](https://github.com/github/docs/issues) to find one that interests you. As a general rule, we don’t assign issues to anyone. If you find an issue to work on, you are welcome to open a PR with a fix.

### Make Changes

#### Make changes locally


1. Fork the repository.
  - Using GitHub Desktop:
    - [Getting started with GitHub Desktop](https://docs.github.com/en/desktop/installing-and-configuring-github-desktop/getting-started-with-github-desktop) will guide you through setting up Desktop.
    - Once Desktop is set up, you can use it to [fork the repo](https://docs.github.com/en/desktop/contributing-and-collaborating-using-github-desktop/cloning-and-forking-repositories-from-github-desktop)!

  - Using the command line:
    - [Fork the repo](https://docs.github.com/en/github/getting-started-with-github/fork-a-repo#fork-an-example-repository) so that you can make your changes without affecting the original project until you're ready to merge them.

2. Create a working branch and start with your changes!

### Commit your update

Commit the changes once you are happy with them. Don't forget to [self-review](#self-review) to speed up the review process:zap:.

### Self review

You should always review your own PR first.

For content changes, make sure that you:

- [ ] Confirm that the changes meet the user experience and goals outlined in the content design plan (if there is one).
- [ ] Compare your pull request's source changes to staging to confirm that the output matches the source and that everything is rendering as expected. This helps spot issues like typos, content that doesn't follow the style guide, or content that isn't rendering due to versioning problems. Remember that lists and tables can be tricky.
- [ ] Review the content for technical accuracy.
- [ ] Copy-edit the changes for grammar, spelling, and adherence to the [style guide](#).
- [ ] Check new or updated Liquid statements to confirm that versioning is correct.
- [ ] If there are any failing checks in your PR, troubleshoot them until they're all passing.


### Pull Request

When you're finished with the changes, create a [pull request](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests).
- Fill the "Ready for review" template so that we can review your PR. This template helps reviewers understand your changes as well as the purpose of your pull request. 
- Don't forget to [link PR to issue](https://docs.github.com/en/issues/tracking-your-work-with-issues/linking-a-pull-request-to-an-issue) if you are solving one.
- Enable the checkbox to [allow maintainer edits](https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/allowing-changes-to-a-pull-request-branch-created-from-a-fork) so the branch can be updated for a merge.
Once you submit your PR, a team member will review your proposal. We may ask questions or request additional information.
- We may ask for changes to be made before a PR can be merged, either using [suggested changes](https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/incorporating-feedback-in-your-pull-request) or pull request comments. You can apply suggested changes directly through the UI. You can make any other changes in your fork, then commit them to your branch.
- As you update your PR and apply changes, mark each conversation as [resolved](https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/commenting-on-a-pull-request#resolving-conversations).
- If you run into any merge issues, checkout this [git tutorial](https://github.com/skills/resolve-merge-conflicts) to help you resolve merge conflicts and other issues.

### Your PR is merged!

Congratulations :tada::tada: The GitHub team thanks you :sparkles:. 

Once your PR is merged, your contributions will be publicly visible on the [GitHub docs](https://docs.github.com/en).


Thanks! :heart: :heart: :heart:

Ready Player Me Team