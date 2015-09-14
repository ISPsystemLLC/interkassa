#include <billmgr/payment/paymentmodule.h>

using namespace payment;

#define BINARY_NAME "pminterkassa"

class InterKassa : public Module {
public:
	InterKassa() : Module("interkassa", "1.0")
	{
		feature_map[PAYMENT_FEATURE_REDIRECT] = true;
		feature_map[PAYMENT_FEATURE_NOT_PROFILE] = true;

		param_map[PAYMENT_PARAM_PAYMENT_SCRIPT] = "/mancgi/2copayment";
	}
};

RUN_MODULE(InterKassa)

