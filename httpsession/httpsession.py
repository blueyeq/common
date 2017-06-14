# _*_ encoding: utf-8
import requests

url='https://open.weixin.qq.com/connect/oauth2/authorize?appid=wx84c07c14a59d0c33&redirect_uri=http%3a%2f%2fwww.hzllpx.com%2fIndex.aspx&response_type=code&scope=snsapi_userinfo&state=Roy&uin=MTM2OTg1MzI4MA%3D%3D&key=68ba5c58377bfaad92520a8351d55a82faed88dc73ffc2d07210f1dc25a6e909f5b15f6f6271131b1bbd27e2c5db84db&version=11020201&pass_ticket=f%2FxhJ9JNoA5y3WTaIdxmpRusv9r6k7qHEejcTQ7WzKmuKZ3z9NS2tw28yVFfMpVJ#wechat_redirect'

url='https://open.weixin.qq.com/connect/oauth2/authorize?appid=wx84c07c14a59d0c33&redirect_uri=http%3a%2f%2fwww.hzllpx.com%2fIndex.aspx&response_type=code&scope=snsapi_userinfo&state=Roy&uin=MTM2OTg1MzI4MA%3D%3D&key=68ba5c58377bfaad8ed6a4bd54d46dc49d544a96eb5b3dde60377e3d53de03e5dc8998f598bcfc471ff66c88e07f10ea&version=11020201&pass_ticket=f%2FxhJ9JNoA5y3WTaIdxmpRusv9r6k7qHEejcTQ7WzKmuKZ3z9NS2tw28yVFfMpVJ#wechat_redirect'

url='https://open.weixin.qq.com/connect/oauth2/authorize?appid=wx84c07c14a59d0c33&redirect_uri=http%3a%2f%2fwww.hzllpx.com%2fIndex.aspx&response_type=code&scope=snsapi_userinfo&state=Roy&uin=MTM2OTg1MzI4MA%3D%3D&key=68ba5c58377bfaadc8822b08789ae462012c19fde1052338a95ad6555aaef2d8a487de0dffffd346a23e7f83b4706a51&version=11020201&pass_ticket=f%2FxhJ9JNoA5y3WTaIdxmpRusv9r6k7qHEejcTQ7WzKmuKZ3z9NS2tw28yVFfMpVJ#wechat_redirect'

url='https://open.weixin.qq.com/connect/oauth2/authorize?appid=wx84c07c14a59d0c33&redirect_uri=http://www.hzllpx.com/Index.aspx&response_type=code&scope=snsapi_userinfo&state=Roy&uin=MTM2OTg1MzI4MA==&key=68ba5c58377bfaad4deb2818690181d2d9784edd75d67b1c4d8481d61e40429c1c3d651b4b4eb88851ec007fbc5104d2&version=11020201&pass_ticket=f/xhJ9JNoA5y3WTaIdxmpRusv9r6k7qHEejcTQ7WzKmuKZ3z9NS2tw28yVFfMpVJ#wechat_redirect'

if __name__ == '__main__':
  s = requests.session()
  r = s.get(url)
  r = s.get('http://www.hzllpx.com/authorization')
  r = s.get('http://www.hzllpx.com/Order.aspx?id=2')
  print r.text
# sw=2;ts=2;sts=2;expandtab
