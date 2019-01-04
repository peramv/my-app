#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_annuitant_invalid_for_acct_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_annuitant_invalid_for_acct_type() { }
		~CIFast_IFast_ifastcbo_err_annuitant_invalid_for_acct_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ANNUITANT_INVALID_FOR_ACCT_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Annuitant entity type may only be set up for non-registered tax types.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Annuitant entity type may only be set up for non-registered tax types.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Rentenempfänger (05)-Objekttyp kann nur für nicht-registrierte Steuerarten erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de entidad de titular de anualidad (05) sólo puede configurarse para tipos tributarios no registrados.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type d'entité prestataire ne peut être réglé que pour les types d'imposition non enregistrés.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheidstype voor lijfrentetrekker (05) kan alleen worden ingesteld voor niet-geregistreerde belastingtypes")); }

        // Actions
	};
}



