#ifndef _TEMPLATE_H_
#define	_TEMPLATE_H_

// ‹[Ž—Singleton
template <class type>
class Singleton
{
public:
	static type *getInstance()
	{
		static type instance;
		return &instance;
	}
};

#endif // !_TEMPLATE_H_
