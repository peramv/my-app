#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_stopdate_invalid_for_buyatnav : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_stopdate_invalid_for_buyatnav() { }
		~CIFast_IFast_ifastcbo_err_stopdate_invalid_for_buyatnav() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_STOPDATE_INVALID_FOR_BUYATNAV")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Stop Date must be earlier than current business date for Buy at NAV model option.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Stop Date must be earlier than current business date for Buy at NAV model option.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'arrêt doit être antérieure à la date opérationnelle actuelle pour l'option de modèle Acheter à la valeur de l'actif net.")); }

        // Actions
	};
}



