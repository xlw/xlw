
#! /usr/bin/env python
#
# $Id$
#
# test the module used to backed up cvs repository for XLW
#

__doc__ = """Backup for xlw cvs repository"""

import urllib

if __name__=='__main__':
        #
        #
        url_name="http://cvs.sourceforge.net/cvstarballs/xlw-cvsroot.tar.gz"
        #
        local_file_name="Y:/backed_up/Linux/cvs_bck/xlw-cvsroot.tar.gz"
        #
        urllib.urlretrieve(url_name, local_file_name)
