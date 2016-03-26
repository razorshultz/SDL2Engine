

template<typename T>
class Count
{
	public:
		Count();
		virtual ~Count();

		virtual void Increment() =0;
		virtual void Decrement() =0;

		T GetValue() const;
		void SetValue(T newValue);
		void Reset();

	protected:
		T value;
		T reset_value;
};

template<typename T>
Count<T>::Count() : value(0), reset_value(0)
{
}

template<typename T>
void Count<T>::Reset()
{
	value = reset_value;
}

template<typename T>
T Count<T>::GetValue() const
{
	return value;
}

template<typename T>
void Count<T>::SetValue(T newValue)
{
	value = newValue;
}

template<typename T>
Count<T>::~Count()
{
}

/////////////////////////////////////////////////////////////////////////

class IntCount: public Count<int>
{
	public:
		IntCount();
		IntCount(int new_value);
		~IntCount();

		void Increment();
		void Decrement();
		char* asBase(int numberBase);

};

IntCount::IntCount()
{
	value = 0;
	reset_value = 0;
}

IntCount::~IntCount()
{
}


IntCount::IntCount(int new_value) 
{
	value = new_value;
}


void IntCount::Increment()
{
	value++;
}


void IntCount::Decrement()
{
	value--;
}










