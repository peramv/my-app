#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_not_preceded_by_good_read : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_not_preceded_by_good_read() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_not_preceded_by_good_read() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_NOT_PRECEDED_BY_GOOD_READ")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Distribution of the same fund/class from and date already exists.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Distribution of the same fund/class from and date already exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verteilung der/des selben Fonds/Klasse und Datum existiert bereits.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La distribución del mismo fondo/clase y fecha ya existe.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Distribution de la même source du fonds/de la classe et de la même date déjà existante")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Distributie van hetzelfde fonds of dezelfde categorie van en datum bestaat al")); }

        // Actions
	};
}



