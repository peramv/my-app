#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_ditabuscore_err_zip_dlvry_office_cde_required : public CConditionObject
	{
	public:
		CBase_Infrastructure_ditabuscore_err_zip_dlvry_office_cde_required() { }
		~CBase_Infrastructure_ditabuscore_err_zip_dlvry_office_cde_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ZIP_DLVRY_OFFICE_CDE_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Zip delivery office code is required for formatted addresses.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Zip delivery office code is required for formatted addresses.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Postamtcode ist für die formatierte Adresse erforderlich.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se requiere el código postal de la oficina de entrega para las direcciones formateadas.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code postal de bureau de livraison est requis pour les adresses postales mises en forme.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Postcode voor bestellingskantoor is vereist voor ingedeelde adressen")); }

        // Actions
	};
}



