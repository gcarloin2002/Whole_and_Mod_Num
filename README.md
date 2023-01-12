# Whole_and_Mod_Num
 These classes allow programmers to initial large integer values and perform arithmetic without having to worry much about overflow as one normally would when working with primitive integer types in the C++ language. The size of the Whole_Num object (or rather the amount of digits in the object), are constrained to the user's operating system maximum size for a vector of chars;

 ## How it is used:
 **Whole_Num**
 
 A Whole_Num object can be initialized similar to how a string is initialized. This class behaves similar to the primitive datatype, int, in which the arithmetic performed on these objects result in values that lack decimal places. There are additional functions and operators in this class however, such as the "!" operator being used as a factorial operation and the "abs()" function to return the absolute value of a Whole_Num.
