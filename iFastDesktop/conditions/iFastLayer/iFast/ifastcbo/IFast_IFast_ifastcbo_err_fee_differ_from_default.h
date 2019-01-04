#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_differ_from_default : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_differ_from_default() { }
		~CIFast_IFast_ifastcbo_err_fee_differ_from_default() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_DIFFER_FROM_DEFAULT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const 
        { 
            if (m_strMarketName == I_("Canada") &&
               (m_strClientName == I_("morganqa") || m_strClientName == I_("clb") || m_strClientName == I_("bob")))
            {
                return 1; 
            }
            else
            {
                return 5; 
            }
        }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Existing acquisition fee differs from the default.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Existierende Abschlussgebühr weicht vom Standard ab.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El cargo por adquisición existente difiere del predeterminado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les frais d'acquisition existants diffèrent des frais par défaut.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bestaande verwervingskosten verschillen van de standaardkosten")); }

        // Actions
	};
}



