# .github-workflows

[![build](https://github.com/ZIMO-Elektronik/.github-workflows/actions/workflows/build.yml/badge.svg)](https://github.com/ZIMO-Elektronik/.github-workflows/actions/workflows/build.yml) [![tests](https://github.com/ZIMO-Elektronik/.github-workflows/actions/workflows/tests.yml/badge.svg)](https://github.com/ZIMO-Elektronik/.github-workflows/actions/workflows/tests.yml)

.github-workflows bundles reuseable [GitHub workflows](https://docs.github.com/en/actions/using-workflows/reusing-workflows).

<img src="data/images/logo.png" width="15%" align="right"/>

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
  </ol>
</details>

## Usage
### arm-none-eabi-gcc
Uses the [arm-none-eabi-gcc](https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain) toolchain to build for various ARM platforms. The `arch` option is mandatory, `target` is optional. If no `target` is specified it defaults to `all`.
```yml
jobs:
  arm-none-eabi-gcc:
    uses: ZIMO-Elektronik/.github-workflows/.github/workflows/arm-none-eabi-gcc.yml@v0.0.1
    with:
      arch: -mcpu=cortex-m4
      target: YourTarget
```

### ctest
Uses CMakes [ctest test driver](https://cmake.org/cmake/help/latest/manual/ctest.1.html) to run unit tests. `target` is optional. If no `target` is specified it defaults to `${{ github.event.repository.name }}Tests`.
```yml
jobs:
  tests:
    uses: ZIMO-Elektronik/.github-workflows/.github/workflows/ctest.yml@v0.0.1
    with:
      target: YourTestTarget
```

### license-checker
Uses the [kt3k license-checker](https://github.com/kt3k/license_checker_github_action) to check if a license is present in the files of a repository.
```yml
jobs:
  license:
    uses: ZIMO-Elektronik/.github-workflows/.github/workflows/license-checker.yml@v0.0.1
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
    uses: ZIMO-Elektronik/.github-workflows/.github/workflows/x86_64-linux-gnu-gcc.yml@v0.0.1
    with:
      target: YourTarget AnotherTarget
```