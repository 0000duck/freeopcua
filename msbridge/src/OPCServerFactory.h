// Author: Alexander Rykovanov 2009
//
// Distributed under the GNU GPL License
// (See accompanying file LICENSE or copy at 
// http://www.gnu.org/copyleft/gpl.html)
//
// $Id:  $
// $Date: $
// $Revision: $

#ifndef __MOZ_OPCSERVERFACTORY__H__
#define __MOZ_OPCSERVERFACTORY__H__


#include <xpcom/nsIFactory.h>

/**
\brief ����� ������� OPC ��������
*/

class OPCServerFactory : public nsIFactory
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIFACTORY

  static char* loader_string;//!< �������� ��� ������
  static char* class_name;   //!< ������ ��� ������ � ������� XPCOM
  static const nsIID kCID;   //!< ������������� ������

  OPCServerFactory ();

private:
  ~OPCServerFactory ();

protected:
  /* additional members */
};

#endif