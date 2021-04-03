
'set variables for reading adc cds cells, and neural model memory
symbol sense1 = w1
symbol sense2 = w2
symbol sense3 = w3
symbol bias = w4
symbol neuronSum = w5

symbol cds1 = 1
symbol cds2 = 3
symbol cds3 = 2


'models a single neuron as described above taht was trained to
'determine whether to turn on or off the motor in regards to 
'the current light level
main:
	'get analog values from cds cells as byte
	readadc cds1, sense1
	readadc cds2, sense2
	readadc cds3, sense3
	
	'convert from byte representation to precent
	let sense1 = sense1 * 100 / 255
	let sense2 = sense2 * 100 / 255
	let sense3 = sense3 * 100 / 255
	
	'assign weights to inputs
	let sense1 = sense1 * 649
	let sense2 = sense2 * 131
	let sense3 = -1000 * sense3
	let bias = 15000
	
	'sum weights and apply activation function
	let neuronSum = sense1 + sense2 + sense3 + bias
	let neuronSum = neuronSum / 400
	
	'if past threshold then trigger motor
	IF neuronSum > 0 THEN
		high portc 1
	ELSE
		low portc 1
	ENDIF
	
	pause 5
	
	goto main