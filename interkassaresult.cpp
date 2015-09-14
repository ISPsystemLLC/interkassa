#include <payment/paymentcgi.h>
#include <mgr/mgrrpc.h>
#include <mgr/mgrdate.h>
#include <mgr/mgrstream.h>
#include <payment/paymentutil.h>
#include <mgr/mgrhash.h>
#include <sstream>

MODULE("interkassaresult");

using namespace payment;

class InterkassaResult : public PaymentCgi {
public:
	InterkassaResult() : PaymentCgi("interkassa", "interkassaresult")
	{
		
	}
	
	virtual string ContentType() 
	{
		return "text/xml";
	}
	
	virtual string ElidParam() 
	{
		return "ik_pm_no";
	}
	
	virtual bool ValidateAuth() {
		return false;
	}
	
	virtual void Process() {
	}
};

RUN_MODULE(InterkassaResult)
