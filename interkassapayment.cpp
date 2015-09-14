#include <payment/paymentcgi.h>
#include <mgr/mgrrpc.h>
#include <mgr/mgrdate.h>
#include <mgr/mgrhash.h>
#include <mgr/mgrstream.h>
#include <sstream>

MODULE("interkassapayment");

using namespace payment;

class InterkassaPayment : public PaymentCgi {
public:
	InterkassaPayment() : PaymentCgi("interkassa", "interkassapayment")
	{
		
	}
	
	virtual bool ValidateAuth() {
		return true;
	}
	
	virtual void Process() {
		StringMap payment_form_param;
		payment_form_param["ik_ia_u"] = GetServerUrl()  + "/mancgi/interkassaresult";
		payment_form_param["ik_suc_u"] = GetSuccessPage();
		payment_form_param["ik_fal_u"] = GetFailPage();
		payment_form_param["ik_co_id"] = Method("ik_co_id");
		payment_form_param["ik_pm_no"] = Payment("id");
		payment_form_param["ik_cur"] = str::Upper(Currency("iso"));
		payment_form_param["ik_am"] = Payment("amount");
		payment_form_param["ik_am_ed"] = "0";
		payment_form_param["ik_desc"] = Payment("description");
		payment_form_param["ik_ia_m"] = "POST";
		payment_form_param["ik_suc_m"] = "GET";
		payment_form_param["ik_fal_m"] = "GET";
		
		string ik_sign_str;
		ForEachI(payment_form_param, p) {
			str::inpl::Append(ik_sign_str, p->second, ":");
		}
		ik_sign_str += ":" + Method("secret");

		string ik_sign = str::base64::Encode(mgr_hash::md5(ik_sign_str));
		
		string form_str = "<html>\n"
						"<head>"
						"	<meta http-equiv='Content-Type' content='text/html; charset=UTF-8'/>\n"
						"	<link rel='shortcut icon' href='billmgr.ico' type='image/x-icon'/>\n"
						"	<script language='JavaScript'>\n"
						"		function DoSubmit() {\n"
						"			document.interkassaform.submit();\n"
						"		}\n"
						"	</script>\n"
						"</head>\n"
						"<body onload='DoSubmit()'>\n"
						"	<form name='interkassaform' action='https://sci.interkassa.com/' method='post'>\n"
						"		<input type='hidden' name='ik_sign' value='" + ik_sign + "'>\n";
		
		ForEachI(payment_form_param, p) {
			str::inpl::Append(form_str, 
						"		<input type='hidden' name='" + p->first + "' value='" + p->second + "'>", "\n");
		}

		form_str +=		"	</form>\n"
						"</body>\n"
						"</html>\n";
		
		std::cout << form_str;
	}
};

RUN_MODULE(InterkassaPayment)
