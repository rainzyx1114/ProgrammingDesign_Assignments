import asyncio
import pyppeteer as pyp
import bs4
import requests

async def getWordInfo(base_url):
    with open('./words.txt', 'r', encoding='utf-8') as f:
        words = [word.strip() for word in f.readlines()]
    browser = await pyp.launch(executablePath=r"C:\Program Files\Google\Chrome\Application\chrome.exe") 
    page = await browser.newPage()
    with open('./results.txt', 'w', encoding='utf-8') as res_file:
        for word in words:
            # print(word)
            url = base_url + word
            await page.goto(url)
            # print(await page.title())
            await asyncio.sleep(2)
            html = await page.content()
            # print(html[:5000])
            soup = bs4.BeautifulSoup(html, 'html.parser')
            diva = soup.find(name='div', attrs={'id' : 'synoid'})
            # print(diva)
            if diva:
                # print('hi')
                res_file.write('$' + word + '\n')
                similar_words = diva.find_all(name='span', attrs={'class': 'p1-4 b_alink'})
                for similar_word in similar_words:
                    similar_word = similar_word.text.strip()
                    res_file.write(similar_word+'\n')
            diva = soup.find(name='div', attrs={'class': 'img_area'})
            if diva:
                img_link = diva.find(name='img')['src']
                img = requests.get(img_link, stream=True)
                with open('./{0}.png'.format(word), 'wb') as img_file:
                    img_file.write(img.content)
    await browser.close()
base_url = "https://cn.bing.com/dict/search?q="
asyncio.run(getWordInfo(base_url))