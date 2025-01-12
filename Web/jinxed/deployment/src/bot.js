import puppeteer from 'puppeteer';

const APP_URL = process.env.APP_URL || 'http://localhost:3000';
const FLAG = process.env.FLAG || 'inctfj{P3RH4P5_E330RS_W3R3_TH3_W4Y_T0_5UCC33D}';
const allowedDomains = (process.env.ALLOWED_DOMAINS || 'localhost').split(',');

const sleep = (ms) => new Promise(resolve => setTimeout(resolve, ms));

export const visit = async (url) => {
  try {
    if (!/^https?:\/\//i.test(url)) {
      url = `http://${url}`;
    }

    const parsedUrl = new URL(url);

    // Check if the domain is allowed
    if (!allowedDomains.includes(parsedUrl.hostname)) {
      throw new Error(`Domain ${parsedUrl.hostname} is not allowed`);
    }

    console.log(`start: ${url}`);

    const browser = await puppeteer.launch({
      headless: true,
      args: [
        '--no-sandbox',
        '--disable-dev-shm-usage',
      ],
    });

    const page = await browser.newPage();

    await page.goto(APP_URL, { timeout: 5000 });

    await page.setCookie({
      name: 'flag',
      value: FLAG,
      domain: 'localhost',
      path: '/',
      httpOnly: false,
      secure: false,
    });

    console.log('Flag set in the bot\'s cookie storage.');

    await page.goto(parsedUrl.toString(), { timeout: 5000 });
    await sleep(5000); 
    await page.close();

    await browser.close();
    console.log(`end: ${url}`);
  } catch (e) {
    console.error('Invalid URL or Error during visit:', e);
  }
};
