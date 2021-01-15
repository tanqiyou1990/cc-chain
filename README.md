CCGO Core integration/staging tree
=====================================

https://www.qk188.cn

What is CCGO?
----------------

CCGO is an experimental digital currency that enables instant payments to anyone, anywhere in the world. CCGO uses peer-to-peer technology to operate with no central authority: managing transactions and issuing money are carried out collectively by the network. CCGO Core is the name of open source software which enables the use of this currency.
CCGO is a merge-minable SHA256 coin which provides an array of useful services which leverage the bitcoin protocol and blockchain technology.

CC总量量9600万枚，每三个⽉月递减10%，举例例：9600 万*10%=960 万/90 天=10.6666667万，第⼀季度960万，每天释放10.6666667万，第二季度9600万减一季度960*10*=9504/90天=9.58933333万，以此类推。
分配⽐比例例：
⽤用户50%，技术6%，运营24%（其中包括：超级合伙⼈人5%、合伙⼈人3%、云商3%5000为1份、决策委3%、公司运营10%》，节点：20%（标准节点17%，平均分配所有节点按照时间先后顺序。社群节点1.5%、社区节点1%、超级节点0.5 %。）

License
-------

CCGO Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](src/test/README.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`. Further details on running
and extending unit tests can be found in [/src/test/README.md](/src/test/README.md).

There are also [regression and integration tests](/test), written
in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/test) are installed) with: `test/functional/test_runner.py`

The Travis CI system makes sure that every pull request is built for Windows, Linux, and macOS, and that unit/sanity tests are run automatically.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.
