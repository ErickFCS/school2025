import "dotenv/config";


export const PORT = process.env.PORT || 3000;
export const POSTGRES_URI = process.env.POSTGRES_URI || "no uri";
export const JWT_SECRET = process.env.JWT_SECRET || "no secret";
