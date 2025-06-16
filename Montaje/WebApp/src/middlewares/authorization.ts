import { Request } from "../types/express.js";
import { jwtPayloadSchema } from "../types/jwtPayload.js";
import { JWT_SECRET } from "../utils/config.js";
import { NextFunction, Response } from "express";
import jwt from "jsonwebtoken";


export const tokenExtractor = async (req: Request, res: Response, next: NextFunction) => {
    const token = req.headers.authorization?.replace("Bearer ", "") || "";
    if (token) {
        const { id } = jwtPayloadSchema.parse(jwt.verify(token, JWT_SECRET));
        req.userId = id;
    }
    next();
};

