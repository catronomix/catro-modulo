
# Catro/Modulo modules for VCV Rack

### CM 0.6.6 has been released, please see release notes: <br>https://github.com/catronomix/catro-modulo/releases/tag/0.6.6

![screenshot1](https://github.com/catronomix/catro-modulo/blob/master/CM066.PNG?raw=true)

Full manual (old version, update will follow): <br> https://github.com/catronomix/catro-modulo/blob/master/CM-manual-v0.6.4.pdf

CM-1: 8xlfo <br>
8 LFOs that blend between sine, square, saw and triangle waves
Rate is from very very slow to audio rate
The rate can be synced to a bpm cv signal from vcClk (from /32 up to x32)
Mix output is the average of all LFOs with a connected output

CM-2: 8xatn<br>
8 attenuverters with scale and offset parameters, as well as modulation cv inputs
Mix output is the average of all outputs that have an input connected
x2 overdrive switch for amplifying signals (useful for changing ±5V to ±10V)

CM-3: PreSetSeq<br>
Preset sequencer and morpher 
8 'Eyes' that set their value when no input connected, or scale the input when connected.
8 triggerable record buttons that save the resulting eye-values
Scan/select dial to choose which saved recording to select for output
Morph slider fades between recording output, direct eye output and recordingXdirect output
Sequencer with some built-in patterns and basic controls
Don't press the "Try me"-button! ;)

CM-4: vcClk<br>
Voltage controlled bpm clock
The gold-plated in and outputs are for the bpm sync signal, for which standards are shared between all the other modules to enable synced bpm changes. Simply chain the bpm cv between the modules, and connect all reset inputs to the vcClk reset output

CM-5: vcClk++<br>
Clock multiplier for vcClk, it outputs 7 clock pulses that are synced with the input
It also outputs 7 bpm sync cv's, which can be used to connect to the ++ bpm input, which will be added up before setting the rate for the clock pulse outputs.

CM-6: 1hp blank<br>
It is a blank panel and it is 1hp wide :)

CM-7: vcClk--<br>
Like vcClk++, but this one divides the clock rate, and the -- bpm input substracts from the first bpm input.

CM-8: aAvsBb<br>
Hybrid comparator/wavefolder:
Set a lower threshold (a), and an upper threshold (b) to control folding and clipping of signals (A) and (B)
Compare (A) and (B) with eachother and with the range (a to b)
Noise generator when nothing is plugged in (A) or (B) and an s&h trigger input for quantized results.

CM-9: 1-8-1
This multifunctional module can act as a selector/router/switch as well as a modulation and gate sequencer, depending on which ports are connected.

CM-10: bitStep
If you want to pass on binary values step by step, this is the module you are looking for.
There are also buttons and trigger inputs to capture the current state and play it back (bit override)

&nbsp;

## The next update will be 1.0, which will be simply 0.6.6 ported to Rack v1 plugin format.
### Additional modules (bitCrawl, bitShift and OctoLove) will have to wait untill that is finished.
