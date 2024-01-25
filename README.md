# .github-workflows

[![build](https://github.com/ZIMO-Elektronik/.github-workflows/actions/workflows/build.yml/badge.svg)](https://github.com/ZIMO-Elektronik/.github-workflows/actions/workflows/build.yml) [![tests](https://github.com/ZIMO-Elektronik/.github-workflows/actions/workflows/tests.yml/badge.svg)](https://github.com/ZIMO-Elektronik/.github-workflows/actions/workflows/tests.yml)

<img src="data/images/logo.png" width="15%" align="right"/>

.github-workflows bundles reusable [GitHub workflows](https://docs.github.com/en/actions/using-workflows/reusing-workflows).

<details>
  <summary>Table of contents</summary>
  <ol>
    <li><a href="#usage">Usage</a></li>
      <ul>
        <li><a href="#arm-none-eabi-gcc">arm-none-eabi-gcc</a></li>
        <li><a href="#ctest">ctest</a></li>
        <li><a href="#license-checker">license-checker</a></li>
        <li><a href="#x86_64-linux-gnu-gcc">x86_64-linux-gnu-gcc</a></li>
      </ul>
    <li><a href="#limitations">Limitations</a></li>
      <ul>
        <li><a href="#tags">Tags</a></li>
        <li><a href="#running-github-actions-locally">Running GitHub actions locally</a></li>
      </ul>
  </ol>
</details>

## Usage
### arm-none-eabi-gcc
Uses the [arm-none-eabi-gcc](https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain) toolchain to build for various ARM platforms. The `arch` option is mandatory, `target` is optional. If no `target` is specified it defaults to `all`. Additional arguments to CMake can be passed with `args`.
```yml
jobs:
  arm-none-eabi-gcc:
    uses: ZIMO-Elektronik/.github-workflows/.github/workflows/arm-none-eabi-gcc.yml@v0.0.3
    with:
      arch: -mcpu=cortex-m4
      args: -DCMAKE_BUILD_TYPE=Release
      target: YourTarget
```

### ctest
Uses CMakes [ctest test driver](https://cmake.org/cmake/help/latest/manual/ctest.1.html) to run unit tests. `target` is optional. If no `target` is specified it defaults to `${{ github.event.repository.name }}Tests`.
```yml
jobs:
  tests:
    uses: ZIMO-Elektronik/.github-workflows/.github/workflows/ctest.yml@v0.0.3
    with:
      target: YourTestTarget
```

### license-checker
Uses the [kt3k license-checker](https://github.com/kt3k/license_checker_github_action) to check if a license is present in the files of a repository.
```yml
jobs:
  license:
    uses: ZIMO-Elektronik/.github-workflows/.github/workflows/license-checker.yml@v0.0.3
```

The check requires a `.licenserc.json` file in the root of the repository.
```json
{
  "{include,src}/**/*.{cpp,hpp}": [
    "// This Source Code Form is subject to the terms of the Mozilla Public",
    "// License, v. 2.0. If a copy of the MPL was not distributed with this",
    "// file, You can obtain one at https://mozilla.org/MPL/2.0/."
  ]
}
```

### x86_64-linux-gnu-gcc
Uses a linux GCC toolchain to build for x86_64 platforms. The `target` option is optional. If no `target` is specified it defaults to `all`.
```yml
jobs:
  x86_64-linux-gnu-gcc:
    uses: ZIMO-Elektronik/.github-workflows/.github/workflows/x86_64-linux-gnu-gcc.yml@v0.0.3
    with:
      args: -DCMAKE_BUILD_TYPE=Release
      target: YourTarget AnotherTarget
```

## Limitations
### Tags
:warning: For whatever reason this repository **must not** use annotated git tags. I came across this through the following [comment](https://github.com/orgs/community/discussions/48693#discussioncomment-6132963) in a GitHub discussion:
> I finally found out what is precisely the problem.
> 
> Well, in the [GH doc](https://docs.github.com/en/enterprise-server@3.7/actions/using-workflows/reusing-workflows#calling-a-reusable-workflow) it mentions that a `release tag` is needed, or a branch or a commit id.
> 
> The term `release tag` is inappropriate in the documentation, because we tested with a Git tag promoted in GitHub as a GitHub Release and it doesn't work better.
> 
> However, we figured out that if we use only a **lightweight Git tag** (rather than an **annotated git tag**), it works. So, as a result, for GitHub Workflows repositories, we need to **avoid using annotated tags**. This seem not possible to forbid as a configuration, so we need to be careful.
> 
> Anyway, GitHub doc is really confusing an not sufficient precise, which is too bad. Moreover, it is surprising that annotated tags doesn't work as their have _more_ information inside. It seems that it such lack a resolution command... maybe could it be fixed in next version ?

:warning: **tl;dr only use lightweight tags for versioning!**

### Running GitHub actions locally
:warning: To support running actions locally we currently can't use relative paths to workflows. This is a known issue with [act](https://github.com/nektos/act) ([#1875](https://github.com/nektos/act/issues/1875)).

:warning: **tl;dr when pushing a new tag, update existing ones!**