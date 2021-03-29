enum Charsets {
	Default = Charset(0),
	UTF8 = Charset(65001),
	UNICODE = Charset(1200)
}

@CLang("String__sl")
class String {
	init(byte[] str, Charset charset=Charsets.Default)
	init(int value)
	init(long value)
	init(float value)
	init(double value)
	init(bool value){
		init( value ? "true" : "false" )
	}
	init(String value)

	@CLang("at__String__sl")
	func at(long index) : char
	func size() : long
	// operator == (String str): bool
	func compare(String another)
	func sub(ulong index, ulong size)
	func bytes(Charset charset=Charsets.UTF8) : byte[]
	operator + (String value): String
	operator + (var value): String {
		return this + String(value)
	}

	// finalize
}


