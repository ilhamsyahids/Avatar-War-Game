[ADT NAMING CONVENTIONS]
The ADT headers made are made as base
You can add more method if needed
But please make sure to follow this convention in method making
Thank you

Constant & Typedef:
	<Type><What>

Predikat:
	<Is/Can><Type><What>
	<Type><Has><What>

Constructor:
	<Type>CreateEmpty
	<Type>Create
	<Type>Initialize

Destructor:
	<Type>Dealokasi

Selector Get:
	<Type>Get<Attribute>

Selector Set:
	<Type>Set<Attribute>

Other Methods:
	<Type><Action>

Number Element = NBElmt
Max Element = MaxElement

Element will always be written Element except in NBElmt

[ADT CATEGORIZATION CONVENTION]
For easier categorization, methods of ADT will be divided into 4 types:
1. SELECTOR -> Accessor of Attributes, use this to set and get
				attributes value

2. CONSTRUCTOR -> Everything about creating and initialization the ADT
				  e.g QueueCreateEmpty(), BuildingInitialization()
				  One thing to note, all base ADT (player, building, skill) returns itself in constructor,
				  while other ADT are procedures (return void)

3. DESTRUCTOR -> Deallocation of ADT
				 e.g ImplicitArrayDealokasi()
4. PREDIKAT -> Methods to evaluate ADT to something
			   e.g IsStackFull(), CanBuildingAttack()

5. <ADT-NAME> OPERATIONS -> Everything other than the above
							Read and print goes here 

Mohon maaf terjadi perubahan kategorisasi yang besar,
terutama untuk selektor Set.
Baru disadari kalau selektor dan konstan menggunakan define tidak
akan bermasalah jika penamaannya unik.