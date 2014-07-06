#ifndef __OpcUaStackCore_OpcUaArray_h__
#define __OpcUaStackCore_OpcUaArray_h__


#include "boost/shared_ptr.hpp"
#include <stdint.h>
#include <iostream>
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/BuildInTypes/ByteOrder.h"

namespace OpcUaStackCore
{

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// global functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	template<typename T>
	  void opcUaBinaryEncode(std::ostream& os, const T& value)
	  {
		  os << value;
	  }

	template<typename T>
	  void opcUaBinaryDecode(std::istream& is, T& value)
	  {
		  is >> value;
	  }

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// class OpcUaArray
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	template<typename T>
	class OpcUaArray 
	{
	  public:
		OpcUaArray(uint32_t maxArrayLen = 1);
		~OpcUaArray(void); 

		void resize(uint32_t maxArrayLen);
		uint32_t size(void);
		uint32_t maxSize(void);
		void clear(void);

		bool set(uint32_t pos, const T& value);
		bool set(const T& valueSPtr);
		bool push_back(const T& value);
		bool get(uint32_t pos, T& value);
		bool get(T& value);

		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

	  private:
		void initArray(void);
		void clearArray(void);

		uint32_t maxArrayLen_;
		uint32_t actArrayLen_;

		T* valueArray_;
		T value_;
	};

	template<typename T>
	OpcUaArray<T>::OpcUaArray(uint32_t maxArrayLen)
	: maxArrayLen_(maxArrayLen)
	, actArrayLen_(0)
	{
		initArray();
	}

	template<typename T>
	OpcUaArray<T>::~OpcUaArray(void)
	{
		clearArray();
	}

	template<typename T>
	void
	OpcUaArray<T>::initArray(void)
	{
		if (maxArrayLen_ == 1) {
			valueArray_ = &value_;
		}
		else {
			valueArray_ = new T[maxArrayLen_];
		}
		actArrayLen_ = 0;
	}

	template<typename T>
	void
	OpcUaArray<T>::clearArray(void)
	{
		if (maxArrayLen_ != 1) {
			delete [] valueArray_;
		}
		valueArray_ = NULL;

		actArrayLen_ = 0;
		maxArrayLen_ = 1;
	}

	template<typename T>
	void
	OpcUaArray<T>::resize(uint32_t maxArrayLen)
	{
		clearArray();
		maxArrayLen_ = maxArrayLen;
		initArray();
	}

	template<typename T>
	uint32_t
	OpcUaArray<T>::size(void)
	{
		return actArrayLen_;
	}

	template<typename T>
	uint32_t
	OpcUaArray<T>::maxSize(void)
	{
		return maxArrayLen_;
	}

	template<typename T>
	void
	OpcUaArray<T>::clear(void)
	{
		clearArray();
		initArray();
	}

	template<typename T>
	bool
	OpcUaArray<T>::set(uint32_t pos, const T& value)
	{
		if (pos >= maxArrayLen_) {
			return false;
		}
		valueArray_[pos] = value;

		if (pos+1 > actArrayLen_) {
			actArrayLen_ = pos + 1;
		}
		return true;
	}

	template<typename T>
	bool
	OpcUaArray<T>::set(const T& value)
	{
		return set(0, value);
	}

	template<typename T>
	bool
	OpcUaArray<T>::push_back(const T& value)
	{
		return set(actArrayLen_, value);
	}

	template<typename T>
	bool 
	OpcUaArray<T>::get(uint32_t pos, T& value)
	{
		if (pos >= actArrayLen_) {
			return false;
		}

		value = valueArray_[pos];
		return true;
	}

	template<typename T>
	bool 
	OpcUaArray<T>::get(T& value)
	{
		return get(0, value);
	}
		
	template<typename T>
	void 
	OpcUaArray<T>::opcUaBinaryEncode(std::ostream& os) const
	{
		int32_t actArrayLen;
		actArrayLen = actArrayLen_;
		OpcUaStackCore::opcUaBinaryEncodeNumber(os, actArrayLen_);

		if (actArrayLen_ <= 0) {
			return;
		}

		for (uint32_t idx=0; idx<actArrayLen_; idx++) {
			OpcUaStackCore::opcUaBinaryEncode(os, valueArray_[idx]);
		}
	}
	
	template<typename T>
	void 
	OpcUaArray<T>::opcUaBinaryDecode(std::istream& is)
	{
		int32_t arrayLength;
		OpcUaStackCore::opcUaBinaryDecodeNumber(is, arrayLength);
		if (arrayLength <= 0) {
			return;
		}

		resize(arrayLength);
		for (int32_t idx=0; idx<arrayLength; idx++) {
			T value;
			OpcUaStackCore::opcUaBinaryDecode(is, value);
			push_back(value);
		}
	}



	template<typename T>
	void opcUaBinaryEncode(std::ostream& os, const OpcUaArray<T>& value)
	{
		value.opcUaBinaryEncode(os);
	}

	template<typename T>
    void opcUaBinaryDecode(std::istream& is, OpcUaArray<T>& value)
	{
		value.opcUaBinaryDecode(is);
	}


	// ---------------------------------------------------------------------------
	// ---------------------------------------------------------------------------
	//
	// class OpcUaArray
	//
	// ---------------------------------------------------------------------------
	// ---------------------------------------------------------------------------
	template<typename T>
	class OpcUaArray<boost::shared_ptr<T> >
	{
	  public:
		OpcUaArray(uint32_t maxArrayLen = 1);
		~OpcUaArray(void); 

		void resize(uint32_t maxArrayLen);
		uint32_t size(void);
		uint32_t maxSize(void);
		void clear(void);

		bool set(uint32_t pos, const boost::shared_ptr<T> value);
		bool set(const boost::shared_ptr<T> valueSPtr);
		bool push_back(const boost::shared_ptr<T> value);
		bool get(uint32_t pos, boost::shared_ptr<T>& value);
		bool get(boost::shared_ptr<T>& value);

		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

	  private:
		void initArray(void);
		void clearArray(void);

		uint32_t maxArrayLen_;
		uint32_t actArrayLen_;

		typename boost::shared_ptr<T>* valueArray_;
		typename boost::shared_ptr<T> value_;
	};

	template<typename T>
	OpcUaArray<boost::shared_ptr<T> >::OpcUaArray(uint32_t maxArrayLen)
	: maxArrayLen_(maxArrayLen)
	, actArrayLen_(0)
	{
		initArray();
	}

	template<typename T>
	OpcUaArray<boost::shared_ptr<T> >::~OpcUaArray(void)
	{
		clearArray();
	}

	template<typename T>
	void
	OpcUaArray<boost::shared_ptr<T> >::initArray(void)
	{
		if (maxArrayLen_ == 1) {
			valueArray_ = &value_;
		}
		else {
			valueArray_ = new boost::shared_ptr<T>[maxArrayLen_];
		}
		actArrayLen_ = 0;
	}

	template<typename T>
	void
	OpcUaArray<boost::shared_ptr<T> >::clearArray(void)
	{
		if (maxArrayLen_ != 1) {
			delete [] valueArray_;
		}
		valueArray_ = NULL;

		actArrayLen_ = 0;
		maxArrayLen_ = 1;
	}

	template<typename T>
	void
	OpcUaArray<boost::shared_ptr<T> >::resize(uint32_t maxArrayLen)
	{
		clearArray();
		maxArrayLen_ = maxArrayLen;
		initArray();
	}

	template<typename T>
	uint32_t
	OpcUaArray<boost::shared_ptr<T> >::size(void)
	{
		return actArrayLen_;
	}

	template<typename T>
	uint32_t
	OpcUaArray<boost::shared_ptr<T> >::maxSize(void)
	{
		return maxArrayLen_;
	}

	template<typename T>
	void
	OpcUaArray<boost::shared_ptr<T> >::clear(void)
	{
		clearArray();
		initArray();
	}

	template<typename T>
	bool
	OpcUaArray<boost::shared_ptr<T> >::set(uint32_t pos, const boost::shared_ptr<T> value)
	{
		if (pos >= maxArrayLen_) {
			return false;
		}
		valueArray_[pos] = value;

		if (pos+1 > actArrayLen_) {
			actArrayLen_ = pos + 1;
		}
		return true;
	}

	template<typename T>
	bool
	OpcUaArray<boost::shared_ptr<T> >::set(const boost::shared_ptr<T> value)
	{
		return set(0, value);
	}

	template<typename T>
	bool
	OpcUaArray<boost::shared_ptr<T> >::push_back(const boost::shared_ptr<T> value)
	{
		return set(actArrayLen_, value);
	}

	template<typename T>
	bool 
	OpcUaArray<boost::shared_ptr<T> >::get(uint32_t pos, boost::shared_ptr<T>& value)
	{
		if (pos >= actArrayLen_) {
			return false;
		}

		value = valueArray_[pos];
		return true;
	}

	template<typename T>
	bool 
	OpcUaArray<boost::shared_ptr<T> >::get(boost::shared_ptr<T>& value)
	{
		return get(0, value);
	}
		
	template<typename T>
	void 
	OpcUaArray<boost::shared_ptr<T> >::opcUaBinaryEncode(std::ostream& os) const
	{
		int32_t actArrayLen;
		actArrayLen = actArrayLen_;
		OpcUaStackCore::opcUaBinaryEncodeNumber(os, actArrayLen_);

		if (actArrayLen_ <= 0) {
			return;
		}

		for (uint32_t idx=0; idx<actArrayLen_; idx++) {
			OpcUaStackCore::opcUaBinaryEncode(os, *valueArray_[idx].get());
		}
	}
	
	template<typename T>
	void 
	OpcUaArray<boost::shared_ptr<T> >::opcUaBinaryDecode(std::istream& is)
	{
		int32_t arrayLength;
		OpcUaStackCore::opcUaBinaryDecodeNumber(is, arrayLength);
		if (arrayLength <= 0) {
			return;
		}

		resize(arrayLength);
		for (int32_t idx=0; idx<arrayLength; idx++) {
			boost::shared_ptr<T> value;
			value = T::construct();
			OpcUaStackCore::opcUaBinaryDecode(is, *value.get());
			push_back(value);
		}
	}


	template<typename T>
	void opcUaBinaryEncode(std::ostream& os, const OpcUaArray<boost::shared_ptr<T> >& value)
	{
		value.opcUaBinaryEncode(os);
	}

	template<typename T>
    void opcUaBinaryDecode(std::istream& is, OpcUaArray<boost::shared_ptr<T> >& value)
	{
		value.opcUaBinaryDecode(is);
	}


}

#endif