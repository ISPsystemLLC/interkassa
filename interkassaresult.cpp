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
		if (Input("ik_co_id") != Method("ik_co_id")) {
			throw mgr_err::Error("unknow_provider");
		}
		
		if (Input("ik_am") != Payment("amount")) {
			throw mgr_err::Value("amonut");
		}
		
		if (str::Lower(Input("ik_inv_st")) == "process") {
			string ik_sign = Input("ik_sign");
			string sing_str;
			
			ForEachI(input_params, ip) {
				if (str::StartsWith(ip->first, "ik_")) {
					str::inpl::Append(sing_str, ip->second, ":");	
				}
			}
			
			sing_str += ":" + Method("secret");
			string sing = str::base64::Encode(mgr_hash::md5(sing_str));
			
			if (sing != ik_sign) {
				throw mgr_err::Value("signature");
			} else {
				SetPaid(MapToStr(input_params, "\n", ":\t"));
			}
		}
	}
};

RUN_MODULE(InterkassaResult)
