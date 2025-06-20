import { Request as ExpressRequest } from "express";


export interface Request extends ExpressRequest {
    userId: number;
    isAdmin: boolean;
}
