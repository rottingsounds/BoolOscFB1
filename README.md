# BoolOscFB1
*[Till Bovermann](http://tai-studio.org) for the [rottingsounds project](http://rottingsounds.org)*.

A 1bit dsp audio plugin based on JUCE and faust

## Requirements

+ [juce 6](https://juce.com/) installed as a package on your system. See `CmakeLists.txt` and JUCE's own [CMake API howto](https://github.com/juce-framework/JUCE/blob/master/docs/CMake%20API.md#using-find_package) for details.
+ [cmake](cmake.org)
+ ([faust](http://faust.grame.fr/), if you want to change the dsp engine)

## Compile

```sh
cmake -Bbuild
cmake --build build
```

configures and builds in `build` directory. 

## Change the dsp

1. Open the `.dsp`-file residing in the `faust`-directory in an editor of your choice and adjust the dsp to your liking. 
2. Open a terminal, `cd` to the `faust` directory, and generate the faust header file with 
    ```
    faust -i -vec -a faustMinimal.h BoolOscFB1.dsp -o ../source/BoolOscFB1-vec.h
    ```
3. if you changed the names/amount of parameters (`hslider` etc.), you may want to adjust the visible parameters in the `juce` source-code.
3. recompile the juce code
4. use.


## Acknowledgements

The development of this plugin has been funded through [RottingSounds](http://rottingsounds.org) (project AR 445-G24) by the Austrian Science Fund (FWF).

It uses implementations of 1bit oscillators by [Dario Sanfilippo](https://www.dariosanfilippo.com/) and [Till Bovermann](http://tai-studio.org) written in [faust](http://faust.grame.fr/). More faust-based 1bit dsp can be found at the [bitdsp-faust repository](https://github.com/rottingsounds/bitDSP-faust).

## License

unless otherwise noted, the source code is licensed under GPL v.3 (see separate LICENCE file).
