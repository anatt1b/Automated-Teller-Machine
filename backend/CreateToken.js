const crypto = require('crypto').promises;

async function generateToken() {
    const buf = await crypto.randomBytes(64);
    return buf.toString('base64');
}

(async () => {
    const token = await generateToken();
    console.log(token);
})();
